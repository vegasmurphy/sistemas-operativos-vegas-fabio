

#include "puntod.c"

int main(int argc, char *argv[]) 
{ 	
	if(argc==1){
		imprimir_punto_B();
	}
	
	/*Punto C. Imprime con -s 
	 * los datos solicitados
	 * */
	 else{
		if((argc==2) && (!strcmp(argv[1],"-s"))){
			imprimir_punto_C();
		}
	
	/*
	 * Punto D todas las llamadas a funciones van dentro del bucle 'for' que lo
	 * imprime con el retardo correspondiente
	 */
		else{
			if ((argc==4) && (!strcmp(argv[1],"-l")) && (atoi(argv[3])>0) && (atoi(argv[2])>0) ){										
				imprimir_punto_D(atoi(argv[2]),atoi(argv[3]));
			}
			else{
				printf("Argumentos invalidos\nlos comandos validos son:\n-s\n-l a b donde a es el delay y b el tiempo de ejecucion\n");
			}
		}
	}
	return 0;
}

 
/*lee el archivo y imprime las lineas pasadas en un arreglo
 * recibe como parametro un arreglo el cual contiene en 
 * primer lugar la cantidad de datos del arreglo
*/


