#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h> /* pid_t */
#include <errno.h>   /* errno */
#include <wchar.h>
#define BUFFSIZE 256


void Atender_Comando(char* comando[5]){	
	printf("llego");
	char *path;
	int i=0;
	path=getenv("PATH");
	int flag=0;
	while((path[i]!='\0')||(flag==1)) {
		if(path[i]==':'){
			char temp[BUFFSIZE];
			int j;
			for(j=0;j<BUFFSIZE;j++) temp[j]='\0';
			strncpy(temp,path,i);
			printf("%s\n",temp);
			strcat(temp,"/");
			strcat(temp,comando[0]);
			printf("%s\n",temp);

			if(execv(temp,comando)!=-1){
				flag=1;
				printf("se ejecuto\n");
				break;
				}
			strcpy(path,path+i+1);
			printf("%s\n",path);
			i=0;
			}
		i++;
		
		
		}
}
