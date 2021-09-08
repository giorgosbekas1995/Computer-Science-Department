/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTCONST = 258,
    REALCONST = 259,
    IDENT = 260,
    STRING = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    FUNCTION = 266,
    RETURN = 267,
    BREAK = 268,
    CONTINUE = 269,
    AND = 270,
    NOT = 271,
    OR = 272,
    LOCAL = 273,
    TRUE = 274,
    FALSE = 275,
    NIL = 276,
    ASSIGN = 277,
    PLUS = 278,
    MINUS = 279,
    MUL = 280,
    DIV = 281,
    MOD = 282,
    EQUALS = 283,
    DIFF = 284,
    PLUSPLUS = 285,
    MINUSMINUS = 286,
    GREATER = 287,
    LESS = 288,
    GREATEREQ = 289,
    LESSEREQ = 290,
    LEFTBRACE = 291,
    RIGHTBRACE = 292,
    LEFTBRACKET = 293,
    RIGHTBRACKET = 294,
    LEFTPARENTHESIS = 295,
    RIGHTPARENTHESIS = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DOUBLECOLON = 300,
    DOT = 301,
    DOUBLEDOT = 302,
    COMMENT1 = 303,
    COMMENT2 = 304,
    MINUS2 = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 1303 "yacc.y" /* yacc.c:1909  */


	int intVal;
	double realVal;
	char* strVal;
	struct expr* exprNode; 
	struct symbol* symbolNode;

	struct forr* forrNode;
	struct callsu* callsuNode;


#line 118 "yacc.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */
