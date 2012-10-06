#include "ComprobarRutaRelativa.c"
void Atender_Ruta_Absoluta(char *[ARGUMENTOS]);
void Atender_Ruta_Relativa(char *[ARGUMENTOS]);


void Atender_Ruta_Relativa(char *comando[ARGUMENTOS]){
	
	char ruta_relativa[BUFFSIZE];
	char nueva_ruta [BUFFSIZE];
	char Dir_Actual[BUFFSIZE],temp[BUFFSIZE];
	
	getcwd(ruta_relativa,BUFFSIZE);

	
	if(strncmp(comando[0],"..",2)==0)
	{
		strcpy(nueva_ruta,comando[0]+2);
		
		int j;
		
		for(j=0;j<BUFFSIZE;j++)
			temp[j]='\0';
			
		int largo;
		getcwd(Dir_Actual,BUFFSIZE);

		largo=strlen(Dir_Actual);
		
		if(largo>1){
				int i;
				for(i=largo;i>1;i--){
				if(Dir_Actual[i]=='/')
						{break;}
				}
				strncpy(temp,Dir_Actual,i);
		}
		strcat(temp, nueva_ruta);
		
	}else if(strncmp(comando[0],".",1)==0)
			{
				strcpy(ruta_relativa,comando[0]+1);
				strcpy(nueva_ruta, strcat(getcwd(Dir_Actual,BUFFSIZE), ruta_relativa));
				
			}else if(!(strncmp(comando[0],"/",1)!=0)) 	{							

						strcat(ruta_relativa,"/");
						strcat(ruta_relativa, comando[0]);
						strcpy(nueva_ruta, ruta_relativa);

				}else{
						strcat(ruta_relativa,comando[0]);
						strcpy(nueva_ruta, ruta_relativa);
				}
				
	
	if(execv(nueva_ruta, comando) == -1){
		printf("Error: La ruta relativa ingresada es invalida\n");
		exit(0);
		return;
	}
	
}

void Atender_Ruta_Absoluta(char *comando[ARGUMENTOS]){
	
		if(execv(comando[0], comando) == -1)
		{
			printf("Error: Ruta Invalida\n");
			exit(0);
		}
}
