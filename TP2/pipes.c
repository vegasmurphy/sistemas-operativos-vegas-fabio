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
					comando1[i]=comandos[i];
					cant_arg1=i+1;
				}
				else{
					comando2[j]=comandos[i];
					j++;
					cant_arg2=j;
					}
			}
			else{
				flag=0;
				}
		}
		
   //-----------------------------------------fork y pipes----------------------------------------   
      
        int     fd[2];
        pid_t   childpid;
		pipe(fd);  
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)//proceso hijo
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                
				 dup2(fd[1], STDOUT_FILENO);
				 close(fd[1]);
				int valor;
				cant_arg=cant_arg1;
				valor=Evaluar_Comando(comando1);
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
        else//proceso padre
        {//printf("padre\n");
                /* Parent process closes up output side of pipe */
            int status;
			wait(&status);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);// extablezco entrada del pipe como STD INPUT
			int valor;
			cant_arg=cant_arg2;
			valor=Evaluar_Comando(comando2);
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
