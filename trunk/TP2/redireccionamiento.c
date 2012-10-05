#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define STDOUT_FID 1
int cant_arg;
#define STDIN_FID 0
#define BUFFSIZE 256
#define ARGUMENTOS 10
void Atender_Ruta_Absoluta(char* [ARGUMENTOS]);
void Atender_Ruta_Relativa(char* [ARGUMENTOS]);
void Atender_Comando(char* [ARGUMENTOS]);
int Evaluar_Comando(char* [ARGUMENTOS]);
void Verificar_Comando_Ingresado(char* []);

void redireccionamiento(char *comandos[ARGUMENTOS]){
	//printf("algo");
	
	if(!strncmp(comandos[cant_arg-2],"<",1)){
		//printf("algo");
		int fid;
		int flags,perm;
		flags = O_WRONLY|O_CREAT|O_TRUNC;
		perm = S_IWUSR|S_IRUSR;
	
		fid = open(comandos[cant_arg-1], flags, perm);
		

	

		if (fid<0) { //perror("open");
		printf("Error: archivo no valido\n");
		exit(0); }


		close(STDIN_FID); /* stdout def. en stdio.h es un FILE* */

		if (dup(fid)<0) { perror("dup"); exit(1); }
			//printf("hola");
			close(fid);
		//	printf("chau");
	
		
		}
	else{
		//printf("algo");
		int fid;
		int flags,perm;
		flags = O_WRONLY|O_CREAT|O_TRUNC;
		perm = S_IWUSR|S_IRUSR;
	
		fid = open(comandos[cant_arg-1], flags, perm);
		

	

		if (fid<0) { //perror("open");
		printf("Error: archivo no valido\n");
		exit(0); }


		close(STDOUT_FID); /* stdout def. en stdio.h es un FILE* */

		if (dup(fid)<0) { perror("dup"); exit(1); }
			//printf("hola");
			close(fid);
		//	printf("chau");
	

		
		
		
		}
		comandos[cant_arg-2]=NULL;
		comandos[cant_arg-1]=NULL;
		cant_arg=cant_arg-2;
		int valor;
		valor=Evaluar_Comando(comandos);
		//printf("llego");
		switch (valor){
		case 1:
			Atender_Ruta_Absoluta(comandos);
			break;
		case 2:
			Atender_Ruta_Relativa(comandos);
			break;
		case 3:
			Atender_Comando(comandos);
			break;
		}



	}
