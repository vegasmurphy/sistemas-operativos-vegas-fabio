#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 256

int ComprobarRutaRelativa(char *[5]);

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

int ComprobarRutaRelativa(char *argv[5]){
	
		int largo;
	
		largo=strlen(argv[0]);
		printf("Largo = %i\n",largo);
		
		if(largo>1){
				int i;
				for(i=0;i<largo;i++){
					if(argv[0][i]=='/')
					{return 0;}
				}
				
		}		return 1;
}

