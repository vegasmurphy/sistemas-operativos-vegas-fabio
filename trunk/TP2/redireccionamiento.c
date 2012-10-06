#include "pipes.c"
void redireccionamiento(char *comandos[ARGUMENTOS]){
	
	if(!strncmp(comandos[cant_arg-2],"<",1)){
		int fid;
		int flags,perm;
		flags = O_WRONLY|O_CREAT|O_TRUNC;
		perm = S_IWUSR|S_IRUSR;
		fid = open(comandos[cant_arg-1], flags, perm);
		if (fid<0) { 
				printf("Error: archivo no valido\n");
				exit(0); }
		close(STDIN_FID); /* stdout def. en stdio.h es un FILE* */
		if (dup(fid)<0) { perror("dup"); exit(1); }
		close(fid);
	
	
		
		}
	else{
		
			int fid;
			int flags,perm;
			flags = O_WRONLY|O_CREAT|O_TRUNC;
			perm = S_IWUSR|S_IRUSR;
	
			fid = open(comandos[cant_arg-1], flags, perm);
			if (fid<0) { 
					printf("Error: archivo no valido\n");
					exit(0); }
			close(STDOUT_FID); /* stdout def. en stdio.h es un FILE* */
			if (dup(fid)<0) { perror("dup"); exit(1); }
					close(fid);
		}
		
		comandos[cant_arg-2]=NULL;
		comandos[cant_arg-1]=NULL;
		cant_arg=cant_arg-2;
		int valor;
		valor=Evaluar_Comando(comandos);
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
