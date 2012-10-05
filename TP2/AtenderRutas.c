#include "ComprobarRutaRelativa.c"
void Atender_Ruta_Absoluta(char *[ARGUMENTOS]);
void Atender_Ruta_Relativa(char *[ARGUMENTOS]);

//int main(int argc, char *argv[]){
	//strcpy(argv[0],"home/fabio/Escritorio/quepasa/Hola");
	////argv[1]="5";
	////argv[2] = NULL;
	//Atender_Ruta_Relativa(argv);
	
	//return 0;
//}

void Atender_Ruta_Relativa(char *comando[ARGUMENTOS]){
	
	char ruta_relativa[BUFFSIZE];
	char nueva_ruta [BUFFSIZE];
	char Dir_Actual[BUFFSIZE],temp[BUFFSIZE];
	
	getcwd(ruta_relativa,BUFFSIZE);
	//printf("La ruta relativa es %s\n",ruta_relativa);
	
	if(strncmp(comando[0],"..",2)==0)
	{
		strcpy(nueva_ruta,comando[0]+2);
		
		int j;
		
		for(j=0;j<BUFFSIZE;j++)
			temp[j]='\0';
			
		int largo;
		getcwd(Dir_Actual,BUFFSIZE);
		printf("%s\n",Dir_Actual);

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
				
	
	//printf("\nLa ruta relativa es......... %s \n", nueva_ruta);
	
	if(execv(nueva_ruta, comando) == -1){
		printf("Error: La ruta relativa ingresada es invalida\n");
		return;
	}
	
}

void Atender_Ruta_Absoluta(char *comando[ARGUMENTOS]){
	
		printf("%s\n\n", *comando);
		if(execv(comando[0], comando) == -1)
		{
			printf("Error\n");
		}
		printf("Termine\n");
}
