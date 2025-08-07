#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100
#define MAX_HISTORY 100

int main()
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_TOKENS];
	char *history[MAX_HISTORY];
	int history_count=0;
	while(1)
	{
	printf("Uday_shell> ");//shell promt
	
	//read input from user
	if(fgets(input,sizeof(input),stdin)==NULL)
	{
		break;
	}

	//remove newline
	input[strcspn(input,"\n")]='\0';

	//store input in history
	if(history_count<MAX_HISTORY)
	{
		history[history_count]=strdup(input);//copy the string
		history_count++;
	}
	
	//check for history command
	
	if(strcmp(input,"history")==0)
	{
		for(int i=0;i<history_count;i++)
		{
			printf("%d: %s\n",i+1,history[i]);
		}
		continue;
	}

	//Exit condtion normally in all shells user enters exit
	if(strcmp(input,"exit")==0)
	{
		break;
	}


	//tokenize input
	int token_count=0;
	char *token=strtok(input," ");
	while(token!=NULL && token_count<MAX_TOKENS-1)
	{
		args[token_count++]=token;
		token=strtok(NULL," ");
	}
	args[token_count]=NULL;
	
	//cd command (built-in)
	if(args[0] !=NULL && strcmp(args[0],"cd")==0)
	{
		if(args[1]==NULL)
		{
			fprintf(stderr,"cd:expected argument\n");
		}
		else
		{
			if(chdir(args[1])!=0)
			{
				perror("cd failed");
			}
		}
		continue; //skip fork
	}

	int background=0;
	if(token_count>0 && strcmp(args[token_count-1],"&")==0)
	{
		background=-1;
		args[token_count-1]=NULL;//remove & from args
	}



	//fork and exexcute
	
	pid_t pid=fork();
	if(pid==0)
	{
		//child process
		if(execvp(args[0],args)==-1)
		{
			perror("command failed");
		}
		exit(EXIT_FAILURE);

	}
	else if(pid>0)
	{
		//parent process
		if(!background)
		{
			waitpid(pid,NULL,0);//wait for child only if not background
		}
		else
		{
			printf("Process running in background(PID:%d)\n",pid);
		}
	}
	else
	{
		perror("fork failed");
	}
	}

	//free history
	for(int i=0;i<history_count;i++)
	{
		free(history[i]);
	}
	return 0;
}
