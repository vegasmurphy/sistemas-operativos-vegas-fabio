
#include "AtenderRutas.c"

void Atender_Comando(char* comando[ARGUMENTOS]){	


  
	char path[BUFFSIZE],*temp;
	int i=0;
	int j;
	for(j=0;j<BUFFSIZE;j++) path[j]='\0';
	temp=getenv("PATH");
	strcpy(path,temp);
	int flag=0;
	while((path[i]!='\0')||(flag==1)) {
		if(path[i]==':'){
			char temp[BUFFSIZE];
			int j;
			for(j=0;j<BUFFSIZE;j++) temp[j]='\0';
			strncpy(temp,path,i);
			strcat(temp,"/");
			strcat(temp,comando[0]);
			execv(temp,comando);
			strcpy(path,path+i+1);
			i=0;
			}
		i++;
		
		
	}
	printf("Error: Comando no Valido");
	exit(0);
     

    



}
