#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFSIZE 256
void Creador_Prompt(char*);


int main(int argc,char **argv){
	
	char prompt[100];
	Creador_Prompt(prompt);
		//obtencion de comando, impresion de prompt
		char comando[50];
		while(strcmp(comando,"exit"))
		{
			scanf("%s",comando);
			printf("%s \n",comando);
		}
		
	return 0;
}

void Creador_Prompt(char* resultado){
	
	//obtencion de hostname y usuario para prompt
	char buffer[BUFFSIZE+1];
	char user[100];
	char hostname[100];
	gethostname(hostname,100);
	printf("%s\n",hostname);
	FILE *f;
	system("env >/tmp/env");
	f = fopen("/tmp/env","r"); 
	
	while(!feof(f))
	{	
		fgets(buffer,BUFFSIZE+1,f);
		if (!strncmp(buffer,"USERNAME",8))
		{
			strcpy(user,buffer+9);
		}
	}
		
		int size;
		printf("%i",strlen(user));
		size=strlen(user);
		
		char user1[size];
		strncpy(user1,user,size);
		//strcat(user1,hostname);
		printf("%s%s",user1,hostname);
		//printf("%s",hostname);
}
