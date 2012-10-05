#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFSIZE 256
#define ARGUMENTOS 10
int ComprobarRutaRelativa(char *[ARGUMENTOS]);

//int main(int argc, char *argv[])
//{	
		//char hola[BUFFSIZE];
		//argv[0]= "quepasajaj/a";
		
		//int j=0;
		//j=ComprobarRutaRelativa(argv);
		//printf("\nComprobar es %i  \n", j);
		
		//getcwd(hola, BUFFSIZE);
		//printf("%s\n", hola);
	//return 0;
//}

int ComprobarRutaRelativa(char *argv[ARGUMENTOS]){
	
		int largo;
	
		largo=strlen(argv[0]);
		//printf("Largo = %i\n",largo);
		
		if(largo>1){
				int i;
				for(i=0;i<largo;i++){
					if(argv[0][i]=='/')
					{return 1;}
				}
				
		}		return 0;
}

