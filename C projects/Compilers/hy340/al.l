%{

#include <stdlib.h>
#include <stdio.h>

#include "yacc.tab.h"

extern int yyerror(char* yaccProvidedMessage);

%}

%option noyywrap
%option yylineno

INTCONST 	[1-9][0-9]*|0 
REALCONST 	[0-9]+\.[0-9]+ 
IDENT 		[a-zA-Z][a-zA-Z0-9_]*

STRING		"\""

IF						if 
ELSE 					else
WHILE 					while
FOR 					for
FUNCTION				function 
RETURN					return
BREAK					break 
CONTINUE 				continue
AND						and 
NOT 					not
OR 						or
LOCAL					local
TRUE					true 
FALSE 					false
NIL 					nil
ASSIGN 					"="
PLUS 					"+"
MINUS 					"-"
MUL						"*"
DIV 					"/"
MOD 					"%"
EQUALS 					"=="
DIFF					"!=" 
PLUSPLUS				"++"
MINUSMINUS				"--"
GREATER 				">"
LESS 					"<"
GREATEREQ				">="
LESSEREQ 				"<="
LEFTBRACE 				"{"
RIGHTBRACE 				"}"
LEFTBRACKET 			"["
RIGHTBRACKET 			"]"
LEFTPARENTHESIS 		"("
RIGHTPARENTHESIS 		")"
SEMICOLON 				";"
COMMA					","
COLON 					":"
DOUBLECOLON 			"::"
DOT 					"."
DOUBLEDOT 				".."

COMMENT1 				"//".*
COMMENT2				"/*"

SPACE 					[\r \t\v]+
NEWLINE 				[\n]


%%

{IF}					{return IF;} 
{ELSE} 					{return ELSE;}
{WHILE} 				{return WHILE;}
{FOR} 					{return FOR;}
{FUNCTION}				{return FUNCTION;} 
{RETURN}				{return RETURN;}
{BREAK}					{return BREAK;} 
{CONTINUE} 				{return CONTINUE;}
{AND}					{return AND;} 
{NOT}					{return NOT;}
{OR} 					{return OR;}
{LOCAL}					{return LOCAL;}
{TRUE}					{return TRUE;} 
{FALSE} 				{return FALSE;}
{NIL} 					{return NIL;}
{ASSIGN}				{return ASSIGN;}
{PLUS} 					{return PLUS;}
{MINUS}					{return MINUS;}
{MUL}					{return MUL;}
{DIV} 					{return DIV;}
{MOD} 					{return MOD;}
{EQUALS}				{return EQUALS;}
{DIFF}					{return DIFF;} 
{PLUSPLUS}				{return PLUSPLUS;}
{MINUSMINUS}			{return MINUSMINUS;}
{GREATER} 				{return GREATER;}
{LESS} 					{return LESS;}
{GREATEREQ}				{return GREATEREQ;}
{LESSEREQ} 				{return LESSEREQ;}
{LEFTBRACE} 			{return LEFTBRACE;}
{RIGHTBRACE}			{return RIGHTBRACE;}
{LEFTBRACKET} 			{return LEFTBRACKET;}
{RIGHTBRACKET} 			{return RIGHTBRACKET;}
{LEFTPARENTHESIS}		{return LEFTPARENTHESIS;}
{RIGHTPARENTHESIS} 		{return RIGHTPARENTHESIS;}
{SEMICOLON} 			{return SEMICOLON;}
{COMMA}					{return COMMA;}
{COLON}					{return COLON;}
{DOUBLECOLON} 			{return DOUBLECOLON;}
{DOT} 					{return DOT;}
{DOUBLEDOT}				{return DOUBLEDOT;}

{IDENT} 				{yylval.strVal=strdup(yytext); return IDENT;}
{INTCONST} 				{yylval.intVal=atoi(yytext);   return INTCONST;}
{REALCONST} 			{yylval.realVal=atof(yytext);  return REALCONST;}


{COMMENT1} 				{/*return COMMENT1;*/}

{COMMENT2}				{	int r,cnt=-1;
								while((r = input()) && r !=EOF && cnt!=0){
									if(r=='/'){
										r=input();
										if(r=='*'){
											--cnt;
										}else unput(r);
									}
									if(r=='*'){
										r=input();
										if(r=='/'){
											++cnt;
										}else unput(r);
									}
								}
								if(cnt==0)
								{/*return COMMENT2;*/}
								else{
									yyerror("\nError comments\n");
								}
								
							}
						

{STRING}				{


						char * string = NULL;
						int ch = input();
						int cnt = 1;
						int s = 0;
						while(ch != EOF){

							if(ch == '"'){
								s = 1;
								break;
							}

							if(ch!='\\'){
								string = realloc(string, ++cnt);
								string[cnt-2] = ch;
								string[cnt-1] = 0;
							}else {
								
								ch = input();
								
								if(ch!=EOF && ch == 'n'){
									string = realloc(string, ++cnt);
									string[cnt-2] = '\n';
									string[cnt-1] = 0;
								}else
								if(ch!=EOF && ch == 't'){
									string = realloc(string, ++cnt);
									string[cnt-2] = '\t';
									string[cnt-1] = 0;
								}else
								if(ch!=EOF && ch == '"'){
									string = realloc(string, ++cnt);
									string[cnt-2] = '"';
									string[cnt-1] = 0;
								}else
								if(ch!=EOF && ch == '\\'){
									string = realloc(string, ++cnt);
									string[cnt-2] = '\\';
									string[cnt-1] = 0;
								}else if(ch!=EOF){
									string = realloc(string, ++cnt);
									string[cnt-2] = '\\';
									string[cnt-1] = 0;
									unput(ch);
								}else{
									yyerror("STRING not closed!");
								}
							}

							ch = input();
						}
						if(s == 1){
							yytext=string;
							yylval.strVal=strdup(string);
						}else 
							yyerror("STRING not closed!");
						return STRING;
					}

{NEWLINE} {}
{SPACE} {}

<<EOF>> 				{return EOF;}
.						{return EOF;}

%%

