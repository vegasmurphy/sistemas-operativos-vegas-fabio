#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define BUFFSIZE 256 

void lectura_archivo(char[100],char[BUFFSIZE+1],int);
void imprimir_tiempo();
void imprimir_idleTime();
void imprimir_UserTime();
void imprimir_System_Time();
void imprimir_cambios_contexto();
void imprimir_procesos();
void imprimir_Boot_time();
void imprimir_info_memoria();
void imprimir_lista_promedio_cargas();
void imprimir_peticiones_disco();
void imprimir_punto_B();
void imprimir_punto_C();
void imprimir_punto_D(int,int);


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
void imprimir_punto_B(){
		char out[BUFFSIZE+1];
		char buffer[BUFFSIZE+1]; 
	
		//Fecha y hora actual
		time_t *timer;
		time_t t;
		timer=&t;
		time(timer);
		printf("\nTiempo y fecha actual: %s",ctime(timer));
		
		//Nombre de la maquina
		lectura_archivo("/proc/sys/kernel/hostname",buffer,0);
		strcpy(out,buffer);
		printf("Nombre de la Maquina: %s\n\n",out);	
	
		//imprimo CPU Model
		lectura_archivo("/proc/cpuinfo",buffer,4);
		strcpy(out,buffer+13);
		printf("CPU Model: %s",out);
	
		//imprimo CPU type
		lectura_archivo("/proc/cpuinfo",buffer,1);
		strcpy(out,buffer+12);
		printf("CPU Type: %s",out);
	
		//imprimo version kernel
		lectura_archivo("/proc/version_signature",buffer,0);
		printf("Version kernel: %s",buffer);
		imprimir_tiempo();
}

void imprimir_punto_C(){
		imprimir_punto_B();
		
//		float tiempos [4];
		imprimir_idleTime();
		imprimir_UserTime();
		imprimir_System_Time();
		imprimir_cambios_contexto();
		imprimir_procesos();
		imprimir_Boot_time();
}
	
void imprimir_punto_D(int delay,int tiempo){

		int i=0;
		
		imprimir_punto_C();
		imprimir_info_memoria();
		imprimir_lista_promedio_cargas();
		imprimir_peticiones_disco();
			
		for (i=0;i<(tiempo/delay);i++){
			printf("---delay %i segundo/s ---\n",delay);
			sleep(delay);
		
			imprimir_info_memoria();
			imprimir_lista_promedio_cargas();
			imprimir_peticiones_disco();
		}
}

void lectura_archivo(char nombre_archivo[100],char buffer[BUFFSIZE+1],int j)
{														
		char lectura [100][BUFFSIZE+1];
		FILE *fd;
		fd= fopen(nombre_archivo,"r");
		int i=0;
	
		while ((fgets(buffer,BUFFSIZE+1,fd)!=NULL) & (i<100))
		{
			strcpy(lectura[i],buffer);
			i=i+1;
		}
		fclose(fd);
		strcpy(buffer,lectura[j]);
}


int obtener_valor_tiempo(FILE *a, char tiempo[][BUFFSIZE+1],int posicion_dato){
		int i=0;
		char valor[BUFFSIZE+1];
		for(i=0; i<posicion_dato+1; i++){
				fscanf(a, "%s", tiempo[i]);
		}
		strcpy(valor,tiempo[posicion_dato]);
		return atoi(valor);
}

void procesar_tiempos(int tiempo, int valores[4])
{
	valores[0]= tiempo / (86400);
	valores[1]=(tiempo % 86400)/3600;
	valores[2]=(tiempo % 3600)/60;
	valores[3]=(tiempo % 60);
}

void imprimir_tiempo()
{
		FILE *fd;
		fd= fopen("/proc/uptime","r");
		char tiempo[4][BUFFSIZE+1];
		int valor_tiempo;
		int datos_tiempos[4];
		
		valor_tiempo = obtener_valor_tiempo(fd,tiempo,0);
		fclose(fd);
		procesar_tiempos(valor_tiempo, datos_tiempos);
		printf("Uptime: %iD:%iH:%iM:%iS \n",datos_tiempos[0],datos_tiempos[1],datos_tiempos[2],datos_tiempos[3]);
}

void imprimir_idleTime()
{	
		FILE *fd;
		fd= fopen("/proc/uptime","r");
		char tiempo[4][BUFFSIZE+1];
		int valor_tiempo;
		int datos_tiempos[4];
		
		valor_tiempo = obtener_valor_tiempo(fd,tiempo,1);
		fclose(fd);
		procesar_tiempos(valor_tiempo, datos_tiempos);
	
		printf("Idle Time: %iD:%iH:%iM:%iS \n",datos_tiempos[0],datos_tiempos[1],datos_tiempos[2],datos_tiempos[3]);
}

void imprimir_UserTime(){
	
		FILE *fd;
		fd= fopen("/proc/stat","r");
		char tiempo[4][BUFFSIZE+1];
		int valor_tiempo;
		int datos_tiempos[4];
		
		valor_tiempo = obtener_valor_tiempo(fd,tiempo,1);
		fclose(fd);
		procesar_tiempos(valor_tiempo/100, datos_tiempos);
	
		printf("User Time: %iD:%iH:%iM:%iS \n",datos_tiempos[0],datos_tiempos[1],datos_tiempos[2],datos_tiempos[3]);
}
	
void imprimir_System_Time()
{	
		FILE *fd;
		fd= fopen("/proc/stat","r");
		char tiempo[4][BUFFSIZE+1];
		int valor_tiempo;
		int datos_tiempos[4];
		
		valor_tiempo = obtener_valor_tiempo(fd,tiempo,3);
		fclose(fd);
		procesar_tiempos(valor_tiempo/100, datos_tiempos);
	
		printf("System Time: %iD:%iH:%iM:%iS \n",datos_tiempos[0],datos_tiempos[1],datos_tiempos[2],datos_tiempos[3]);
}

void imprimir_cambios_contexto(){
	
		FILE *fd;
		fd= fopen("/proc/stat","r");
		int i=0;
		int flag=1;
		char buffer[BUFFSIZE+1];
		while ((fgets(buffer,BUFFSIZE+1,fd)!=NULL) & (i<100)&(flag))
		{
			i++;
			char out[4];
			char output[BUFFSIZE+1];
			strncpy(out,buffer,4);
			
			if (!strcmp(out,"ctxt")){
			strcpy(output,buffer+5);
			printf("Context Changes: %s",output);
			}
		}
		
		fclose(fd);
}

void imprimir_Boot_time()
{
		FILE *fd;
		fd= fopen("/proc/stat","r");
		int i=0;
		int flag=1;
		char buffer[BUFFSIZE+1];
		while ((fgets(buffer,BUFFSIZE+1,fd)!=NULL) & (i<100)&(flag))
		{
			i++;
			char out[5];
		
			char output[BUFFSIZE+1];
			strncpy(out,buffer,5);
		
			if (!strcmp(out,"btime")){
				strcpy(output,buffer+6);
				//printf("%s \n",output);
				int aux;
				aux=atoi(output);
				//printf("%i",aux);
				time_t *t;
				time_t time1;
				t=&time1;
				time1 = aux;
				printf("Boot Time: %s",ctime(t));
			}
		}

		fclose(fd);
}
	
void imprimir_procesos()
{
		FILE *fd;
		fd= fopen("/proc/stat","r");
		int i=0;
		int flag=1;
		char buffer[BUFFSIZE+1];
		while ((fgets(buffer,BUFFSIZE+1,fd)!=NULL) & (i<100)&(flag))
		{
			i++;
			char out[9];
			char output[BUFFSIZE+1];
			strncpy(out,buffer,9);
		
			if (!strcmp(out,"processes")){
				strcpy(output,buffer+10);
				printf("Total Processes Created: %s",output);
			}
		}
	
		fclose(fd);
}

void imprimir_info_memoria()
{
		FILE *fd;
		fd = fopen("/proc/meminfo", "r");
	
		char  buffer[5][256];
		int i=0;
	
		while(i<5)
		{
			fscanf(fd,"%s",buffer[i]);
			i++;
		}
		printf("Memoria Disponible / Total: %s / %s \n", buffer[4], buffer[1]);
	
		fclose(fd);
}

void imprimir_lista_promedio_cargas()
{	
		FILE	*fd;
		fd = fopen("/proc/loadavg","r");
		char carga[256];
	
		fscanf(fd, "%s", carga);
		float promedio = atof(carga);
		printf("Promedio de carga en el último minuto: %.2f \n", promedio);
		
		fclose(fd);
}

void imprimir_peticiones_disco()
{
		char lectura [100][BUFFSIZE+1];
		FILE *fd;
		fd= fopen("/proc/diskstats","r");
		int i=0;
		char buffer[BUFFSIZE+1];
		int acumulador=0;
		
		while ((fgets(buffer,BUFFSIZE+1,fd)!=NULL) & (i<100))
		{
			if ((!strncmp(buffer+17," ",1)) & ((!strncmp(buffer+13,"sd",2))||(!strncmp(buffer+13,"hd",2))))
			{	
				//printf("%s",buffer+13);
				acumulador += atoi(buffer+17);
				int espacios=0;
				int i=0;
				
				while(espacios<4){
					if (*(buffer+17+i)==' ')
						{espacios++;}
					i++;
				}
				
				acumulador+=atoi(buffer+17+i);
				//printf("%i \n",atoi(buffer+17+i));
				//printf("%i \n",acumulador);
				strcpy(lectura[i],buffer);
				
			}
			i=i+1;
		}
		
		printf("Peticiones a Disco: %i \n",acumulador);
	
		fclose(fd);
}

