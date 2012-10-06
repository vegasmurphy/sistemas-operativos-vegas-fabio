#include "Atender_Comando.c"
void Realizar_cd(char* comandos[ARGUMENTOS]){
	if(!strncmp(comandos[1],"/",1)){
		//printf("ruta antes: %s \n",getcwd(NULL,0));
		if(chdir(comandos[1])){printf("ruta no encontrada \n");}
		//printf("ruta despues: %s \n",getcwd(NULL,0));
		}
	else {
		if(!strncmp(comandos[1],"..",2)){
			char Dir_Actual[BUFFSIZE],temp[BUFFSIZE];
			int j;
			for(j=0;j<BUFFSIZE;j++)temp[j]='\0';
			int largo;
			getcwd(Dir_Actual,BUFFSIZE);
			//printf("%s\n",Dir_Actual);

			largo=strlen(Dir_Actual);
			if(largo>1){
				int i;
				for(i=largo;i>1;i--){
				if(Dir_Actual[i]=='/')
						{break;}
				}
				strncpy(temp,Dir_Actual,i);
				//printf("%s\n",temp);
				if(chdir(temp)){
				printf("ruta no encontrada");
				}
				//printf("ruta despues: %s \n",getcwd(NULL,0));
			}
			
			
			}
		else{
			//printf("ruta antes: %s \n",getcwd(NULL,0));
			char temp[BUFFSIZE],temp1[BUFFSIZE];
			temp[0]='/';
			temp[1]='\0';
			strcat(temp,comandos[1]);
			//printf("strcat bien");
			getcwd(temp1,BUFFSIZE);
			//printf("getcwd ok");
			strcat(temp1,temp);
			//printf("strcat2 ok");
			//printf("%s",temp1);
			if(chdir(temp1)){
				printf("ruta no encontrada");
				}
			//printf("ruta despues: %s \n",getcwd(NULL,0));

			}
		
		}
	}
