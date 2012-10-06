
#include "cd.c"
void Creador_Prompt();
void Ingresar_Comando(char* [5]);



int flag_ejec_background=1;
int main(int argc,char *argv[]){
	int i;
	char *comando[ARGUMENTOS];
	//printf("%s",getenv("PATH"));
		while(1)
		{		
			for(i=0;i<ARGUMENTOS;i++)comando[i]=NULL;
			Creador_Prompt();
			Ingresar_Comando(comando);
			//printf("%s %s ----------",argv[0],argv[1]);
		}
		
		
	return 0;
}

void Creador_Prompt(){
	
	//obtencion de hostname y usuario para prompt
	//char buffer[BUFFSIZE+1];
	char *user;
	char hostname[100];
	gethostname(hostname,100);
	//printf("%s\n",getenv("USER"));
	user=getenv("USER");
	int size;
	size=strlen(user);
	char user1[size];
	strncpy(user1,user,size);
	strcat(user1,hostname);
	printf("\n%s@%s*%s--baash> ",user,hostname,getcwd(NULL,0));
}


void Ingresar_Comando(char *comando[ARGUMENTOS])
{		
	//obtencion de comando y argumentos almacenados en 'comando'
	
	char buffer[256];
	char *t1;
	int i=0,h=0;
	//int j=0;
	//printf("Ingrese comando\n");

	gets(buffer);
	printf("llego\n");

	
	for ( t1 = strtok(buffer," "); t1 != NULL; t1 = strtok(NULL, " ") ){
		comando[i]= t1;
		i++;
	}	
	//printf("%i",i);
	cant_arg=i;
	//for (j=i;j<5;j++) comando[j]=NULL;
	while(h<i){
		//printf("%i  --------   %s\n", h, comando[h]);
		h++;
	}
		
	Verificar_Comando_Ingresado(comando);
}

void Verificar_Comando_Ingresado(char *comando[ARGUMENTOS])
{
	// Crea un proceso hijo para realizar la busqueda y ejecucion del comando ingresado
	//printf("llego verificar");
	printf("llego\n");
	int valor,status;
	valor = Evaluar_Comando(comando);
	//printf("valor: %i\n",valor);
	//printf("evaluar ok");
	if(valor==4){Realizar_cd(comando);}
	else{
	pid_t pID = vfork();
   //printf("%i ",pID);
   if (pID == 0)                // child

   {//printf("entreaca");

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
			//printf("entre");
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

        // Throw exception

    }

    else                                   // parent

    {	if(flag_ejec_background){
		waitpid(pID, &status, 0);
		//printf("ejecuta wait");
		}
     flag_ejec_background=1;
      // Code only executed by parent process

	//printf("%i",flag_ejec_background);

      

	}	

	}
}

int Evaluar_Comando(char *comando[ARGUMENTOS]){
	//printf("llego evaluar");
		// Identifica si el comando ingresado es una ruta absoluta, una ruta relativa o un comando.
		printf("llego");
		int i;
		for(i=0;i<cant_arg;i++){
			if(!strncmp(comando[i],"|",1)){
				printf("llego");
				return 6;
				}
			
			}
		
		
		if((!strncmp(comando[cant_arg-2],"<",1))||(!strncmp(comando[cant_arg-2],">",1)))
			{
			return 5;
			}
		
		
		if(!strncmp(comando[cant_arg-1],"&",1)){
			flag_ejec_background=0;
			comando[cant_arg-1]=NULL;
			}
		
		
		if(comando[0]==NULL){return -1;}
		if (!strncmp(comando[0],"cd",2)){
			return 4;
			}
		else{
			if (!strncmp(comando[0],"exit",4)){
				exit(0);
				}
				else{
					if(!strncmp(comando[0],"/",1))//camino absoluto
						{
						//printf("%s***************",comando[0]);
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





