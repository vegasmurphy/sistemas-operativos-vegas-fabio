#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h> /* pid_t */
#include <errno.h>   /* errno */
#include <wchar.h>
#define BUFFSIZE 256

void Creador_Prompt();
void Ingresar_Comando(char* [5]);
void Verificar_Comando_Ingresado(char* [5]);
int Evaluar_Comando(char* [5]);
void Atender_Ruta_Absoluta(char [5]);
void Atender_Ruta_Relativa(char [5]);
void Atender_Comando(char [5]);

int main(int argc,char *argv[]){
	
	while(1)
		{	
			Creador_Prompt();
			Ingresar_Comando(argv);printf("%s %s ----------",argv[0],argv[1]);
		}
		
		
	return 0;
}

void Creador_Prompt(){
	
	//obtencion de hostname y usuario para prompt
	char buffer[BUFFSIZE+1];
	char user[100];
	char hostname[100];
	gethostname(hostname,100);
	FILE *f;
	system("env >/tmp/env");
	f = fopen("/tmp/env","r"); 

	
	while(!feof(f))
	{	
		fgets(buffer,BUFFSIZE+1,f);
		if (!strncmp(buffer,"USER=",5))
		{
			strcpy(user,buffer+5);
		}
	}
		int size;
		size=strlen(hostname);
		char user1[size];
		strcpy(user1,user);
		strcat(user1,hostname);
		printf("\n%s@ ",user1);
}


void Ingresar_Comando(char *comando[5])
{		
	//obtencion de comando y argumentos almacenados en 'comando'
	
	char buffer[256];
	char *t1;
	int i=0,h=0;
	
	//printf("Ingrese comando\n");

	gets(buffer);
		
	
	for ( t1 = strtok(buffer," "); t1 != NULL; t1 = strtok(NULL, " ") ){
		comando[i]= t1;
		i++;
	}	
	while(h<i){
		printf("%i  --------   %s\n", h, comando[h]);
		h++;
	}
		
	Verificar_Comando_Ingresado(comando);
}

void Verificar_Comando_Ingresado(char *comando[5])
{
	// Crea un proceso hijo para realizar la busqueda y ejecucion del comando ingresado
	
	int valor;
	valor = Evaluar_Comando(comando);
	printf("valor: %i\n",valor);
	
	switch (valor){
		case 1:
			Atender_Ruta_Absoluta(comando[5]);
			break;
		case 2:
			Atender_Ruta_Relativa(comando[5]);
			break;
		case 3:
			Atender_Comando(comando[5]);
			break;
		case 4:
			Realizar_cd(comando[5]);
			break;
	}
}

int Evaluar_Comando(char *comando[5]){
	
		// Identifica si el comando ingresado es una ruta absoluta, una ruta relativa o un comando.
		if (!strncmp(comando[0],"cd",2)){
			return 4;
			}
		else{
			if (!strncmp(comando[0],"exit",4)){
				exit(0);
				}
				else{
					if(!strncmp(comando[0],"/",1))
						{
						printf("%s***************",comando[0]);
						return 1;
						}
					else{
						if(!strncmp(comando[0],".",1)){
						return 2;
						}else return 3;
						}
					}
			}
}

void Atender_Ruta_Relativa(char comando[5]){
	pid_t pid_relativo;
	
	pid_relativo = fork();
	if(pid_relativo == -1){
		printf("Error");
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(pid_relativo == 0)
	{
		printf("Soy Ruta Relativa\n");
		_exit(0);
	}
	else
	{
		printf("Padre--------Ruta Relativa \n");
		return;
	}
}


void Atender_Ruta_Absoluta(char comando[5]){
	pid_t pid_absoluto;
	
	pid_absoluto = fork();
	if(pid_absoluto == -1){
		printf("Error");
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(pid_absoluto == 0)
	{
		printf("Ruta Absoluta\n");
		_exit(0);
	}
	else
	{
		printf("Padre --------- Ruta Absoluta\n");
		return;
	}
}

void Atender_Comando(char comando[5]){	
	pid_t pid_comando;
	
	pid_comando = fork();
	
	if(pid_comando == -1){
		printf("Error");
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(pid_comando == 0)
	{
		printf("por que no entra aca?\n");
		_exit(0);
	}
	else
	{
		printf("Padre--------Comando \n");
		return;
	}	
}
