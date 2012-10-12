
#include "cd.c"
void Creador_Prompt();
void Ingresar_Comando(char* [5]);



int flag_ejec_background=1;
int main(int argc,char *argv[]){
	int i;
	char *comando[ARGUMENTOS];

		while(1)
		{		
			for(i=0;i<ARGUMENTOS;i++)comando[i]=NULL;
			Creador_Prompt();
			Ingresar_Comando(comando);
		
		}
		
		
	return 0;
}

//..............obtencion de hostname y usuario para prompt..........

void Creador_Prompt(){
	
	

	char *user;
	char hostname[100];
	gethostname(hostname,100);
	user=getenv("USER");
	int size;
	size=strlen(user);
	char user1[size];
	strncpy(user1,user,size);
	strcat(user1,hostname);
	printf("\n%s@%s*%s--baash> ",user,hostname,getcwd(NULL,0));
}


//..............obtencion de comando y argumentos almacenados en 'comando'...........
	
void Ingresar_Comando(char *comando[ARGUMENTOS])
{		
	char buffer[256];
	char *t1;
	int i=0;
	gets(buffer);
	for ( t1 = strtok(buffer," "); t1 != NULL; t1 = strtok(NULL, " ") ){
		comando[i]= t1;
		i++;
	}	
	cant_arg=i;	
	Verificar_Comando_Ingresado(comando);
}

// ............Crea un proceso hijo para realizar la busqueda y ejecucion del comando ingresado........
void Verificar_Comando_Ingresado(char *comando[ARGUMENTOS])
{
	
	int valor,status;
	valor = Evaluar_Comando(comando);

	if(valor==4){Realizar_cd(comando);}
	else{
	pid_t pID = vfork();

   if (pID == 0)                // child

   {

	switch (valor){
		case 1:
			Atender_Ruta_Absoluta(comando);
			break;
		case 2:
			Atender_Ruta_Relativa(comando);
			break;
		case 3:
			Atender_Comando(comando);
			break;
		case 5:
			
			redireccionamiento(comando);
			break;
		case 6:
			pipe_process(comando);
			break;
		}
	}
	else if (pID < 0)            // failed to fork

    {
        exit(1);
    }

    else                                   // parent
    {	// Code only executed by parent process
		if(flag_ejec_background){
			waitpid(pID, &status, 0);
		
			}
     flag_ejec_background=1;
      

	

      

	}	

	}
}

//........ Identifica si el comando ingresado es una ruta absoluta, una ruta relativa o un comando.....
		
int Evaluar_Comando(char *comando[ARGUMENTOS]){
	

		
		int i;
		for(i=0;i<cant_arg;i++){
			if(!strncmp(comando[i],"|",1)){
				
				return 6;
				}
			
			}
		
		if(cant_arg>1){
		if((!strncmp(comando[cant_arg-2],"<",1))||(!strncmp(comando[cant_arg-2],">",1)))
			{
			return 5;
			}}
		
		
		if(!strncmp(comando[cant_arg-1],"&",1)){
			flag_ejec_background=0;
			comando[cant_arg-1]=NULL;
			}
		
		
		if(comando[0]==NULL){return -1;}
		if (!strncmp(comando[0],"cd",2)){
			return 4;
			}
		else{
			if (!strcmp(comando[0],"exit")){
				exit(0);
				}
				else{
					if(!strncmp(comando[0],"/",1))//camino absoluto
						{
						
						return 1;
						}
					else{
						if((!strncmp(comando[0],".",1))||ComprobarRutaRelativa(comando)){//camino relativo
						return 2;
						}else return 3;//comando
						}
					}
			}
}






