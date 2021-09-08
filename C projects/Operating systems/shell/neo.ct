/* 
 * My own shell 
 * by Giorgos Bekas
 * Operating Systems - hy345
 * Some system calls I used: 
 * fork(2), exec(3), execv(3), wait(2), waitpid(2), signal(2), kill(1), pipe(2), sh(1), bash(1),
 * chdir(2), getcwd(2), getlogin(2), dup2(2), termios(3)
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>

/* globals */
const char *shell="cs345sh: ";
char name[1024];
char Path[1024],Home[1024];
char terminal[1024];
pid_t bg[65536];
int bgcnt = 0;
jmp_buf env;
char * CWD;
int check_star;
int check_bg;
int check_pipes;
char fullcommand[1024];
char lastcommand[1024];
/* sunarthseis */
unsigned int no_args(char ** args);
void display_prompt();
void nonf_run(char **arguments);
void mypwd();
void mycd(char *param);
void myfg();
void mybg(char ** command, pid_t pid);
void mystar(char ** command);
void mypipes(char ** command);
void signal_handler();
char ** dispatch_input(void);

int main(void)
{
	char **arguments;
	unsigned int noargs,resjmp;
	pid_t pid;
	
	CWD = malloc(1024 * sizeof(char));
	getlogin_r(name, 1024); 
	CWD=getcwd(Home,(size_t)1024);
	ctermid(terminal); /* gia thn fg */
	
	while ( 1 ) {
		check_star = 0;
		check_bg = 0;
		check_pipes = 0;
		strcpy(lastcommand, fullcommand);
		display_prompt();
		
		arguments=dispatch_input();
		if ( ! arguments[0] )	/*patithike enter) */
			continue;
		
		resjmp=setjmp(env);
		if ( resjmp )
			continue;
		
		if (! strcmp(arguments[0],"cd") )
			mycd(arguments[1]);
		else if (! strcmp(arguments[0],"pwd") )
			mypwd();
		else if ( check_star == 1)
			mystar(arguments);
		else if (! strcmp(arguments[0],"fg") )
			myfg();
		else if ( check_pipes == 1)
			mypipes(arguments);
		else if ( strcmp(arguments[0],"exit") == 0 )
			exit(EXIT_SUCCESS);
		else {
			pid = fork();
			if (pid < 0) /* fork error */ {
				syslog( LOG_ERR, "unable to fork , code=%d (%s)",
				errno, strerror(errno) );
				fprintf(stderr,"A Fork error happenned\n");
				exit(EXIT_FAILURE);
			}
			else if ( pid == 0 ) {
				nonf_run(arguments);
				exit(EXIT_SUCCESS);
			}
			else {
				noargs=no_args(arguments) - 1;
				if ( strcmp(arguments[noargs],"&") )
					waitpid (pid,0,0);
				else {
					printf("Background process with pid {%d} and name {%s}\n", pid, arguments[0]);
					mybg(arguments, pid);
					bg[bgcnt++] = pid;
					signal(SIGCHLD,signal_handler);	
				}
			}
		}		
		clearerr(stdin);
		clearerr(stderr);
		clearerr(stdout);
	}
	return EXIT_SUCCESS;
}

void signal_handler(void)
{
	int status;
	while( waitpid(-1, &status, WNOHANG) > 0 );
}

void nonf_run(char **arguments)
{
	char *command=arguments[0];
	unsigned int noargs;
	
	noargs=no_args(arguments) - 1;
	if (arguments[noargs] && strcmp(arguments[noargs],"&")== 0) {
		arguments[noargs]=NULL;
	}
	else
	{
		if ( execvp(command,arguments)==-1)
			printf("%s : %s: command not found\n", shell, command);
		exit(EXIT_SUCCESS);
	}
}

void mycd(char *param)
{
	if (param && param[0] !='~') {
		if( chdir(param) )
			fprintf(stderr,"Mybash : cd: %s: No such file or directory\n",param);
	}
	else
		if ( chdir(Home) )
			fprintf(stderr,"Mybash : cd: %s: No such file or directory\n",Home);
}

void mypwd()
{
	if(getcwd(Path,(size_t)1024) == NULL)
		fprintf(stderr, "Read error in getting current working directory : %s\n",strerror(errno));
	else
		puts(Path);
}

void mybg(char ** command, pid_t pid)
{
	char tmp[1024];
	sprintf(tmp, "bg %d", pid);
	
	system(fullcommand);
	/*system(tmp); */
	memset(tmp, '\0', 1024);
}

void myfg()
{
	int i;
	char tmp[1024];
	if ( lastcommand[strlen(lastcommand) - 1] == '&')
		lastcommand[strlen(lastcommand) - 1] = '\0';
	if (bgcnt == 0)
		printf("Den exeis kapoio process sto background\n");
	
	for (i = 0; i < bgcnt; i++) {
		sprintf(tmp, "fg %d", bg[i]);
		puts(tmp);
		sprintf(tmp, "> /dev/null 2>&1"); 
		system(tmp);
		system(lastcommand);
		
		memset(tmp, '\0', 1024);
	}
	bgcnt = 0;
}

unsigned int no_args(char ** args)
{
	unsigned int c=0;
	for ( ; args[c] ; c++ );
	return c;
}

void display_prompt()
{
	printf("%s@%s%s$ ", name, shell, CWD);
}

void mypipes(char ** command)
{
	system(fullcommand);
}

void mystar(char ** command)
{
	system(fullcommand);
}
char ** dispatch_input()
{
	unsigned int c,argsno=0,size=4,i=0,buffer_size=0;
	char **args=NULL,buffer[1024];
	long int arg_size=0;
	unsigned char WrEn=0;
	int k = 0;
	
	args=(char **)malloc(4 * sizeof(char *) );
	
	while ( (c=getchar()) !='\n' ) {
		buffer[buffer_size++]=c;
		fullcommand[k++] = c;
		if (isspace(c)) {
			if (WrEn) {
				if (argsno+1 > size) {
					size *=2;
					args=(char **)realloc(args,size * sizeof(char *) );
				}
				args[argsno]=(char *) malloc ( (arg_size +1)* sizeof(char) );
				for (i=0; arg_size > 0; arg_size--,i++ ) {
					args[argsno][i]=buffer[buffer_size-1-arg_size];
				}
				args[argsno][i]='\0';
				WrEn=0;
				arg_size=0;
				argsno++;
			}
		}
		else if (c == '*')
			check_star = 1;
		else if ( c == '&')
			check_bg = 1;
		else if ( c == '<' || c == '>' || c == '|')
			check_pipes = 1;
		else {
			arg_size++;
			WrEn=1;
		}
	}
	if ( arg_size ) {
				if (argsno+1 > size) {
					size *=2;
					args=(char **)realloc(args,size * sizeof(char *) );
				}
				args[argsno]=(char *) malloc ( (arg_size +1)* sizeof(char) );
				for (i=0; arg_size > 0; arg_size--,i++ ) {
					args[argsno][i]=buffer[buffer_size-arg_size];
				}
				args[argsno][i]='\0';
				WrEn=0;
				arg_size=0;
				argsno++;
	}
	args[argsno]=NULL;
	return args;
}