#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
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


void pipe_process(char *comandos[ARGUMENTOS]){
	printf("entro en la funcion\n");
	char *comando1[ARGUMENTOS];
	char *comando2[ARGUMENTOS];
	int i,j=0;
	int flag=1;
	int cant_arg1,cant_arg2;
	for(i=0;i<ARGUMENTOS;i++){comando1[i]=NULL;
	comando2[i]=NULL;}
	for(i=0;i<cant_arg;i++){
			if(strncmp(comandos[i],"|",1)){
				if(flag){
				char buffer[BUFFSIZE];
				strcpy(buffer,comandos[i]);
				comando1[i]=buffer;
				cant_arg1=i;
				}
				else{
					char buffer[BUFFSIZE];
					strcpy(buffer,comandos[i]);
					comando2[j]=buffer;
					j++;
					cant_arg2=j;
					}
			}
			else{
				flag=0;
				}
		}
      
      printf("paso for\n");
      
      
        int     fd[2];
        pid_t   childpid;
       // char    string[] = "Hello, world!\n";
        //char    readbuffer[80];
		//int status;
        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
				//int fid;
				
			printf("hijo\n");

				close(STDOUT_FID); /* stdout def. en stdio.h es un FILE* */

				if (dup(fd[1])<0) { perror("dup"); exit(1); }
				//printf("hola");
				close(fd[1]);
				//	printf("chau");
				int valor;
				cant_arg=cant_arg1;
				printf("antes de evaluar comando\n");
				valor=Evaluar_Comando(comando1);
				printf("Evcom ok\n");
                switch (valor){
				case 1:
						Atender_Ruta_Absoluta(comando1);
						break;
				case 2:
						Atender_Ruta_Relativa(comando1);
						break;
				case 3:
						Atender_Comando(comando1);
						break;}
        }
        else
        {printf("padre\n");
                /* Parent process closes up output side of pipe */
                close(fd[1]);
				//waitpid(childpid,&status,0);
			//	int fid;

	
		close(STDIN_FID); /* stdout def. en stdio.h es un FILE* */

		if (dup(fd[0])<0) { perror("dup"); exit(1); }
			//printf("hola");
			close(fd[0]);
		//	printf("chau");
		int valor;
		cant_arg=cant_arg2;
		printf("ante ev com\n");
				valor=Evaluar_Comando(comando2);
				printf("evcom ok\n");
                switch (valor){
				case 1:
						Atender_Ruta_Absoluta(comando2);
						break;
				case 2:
						Atender_Ruta_Relativa(comando2);
						break;
				case 3:
						Atender_Comando(comando2);
						break;}

        }
	
	
	}
