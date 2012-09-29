#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define BUFFSIZE 256



void lectura_archivo(char[100],char[BUFFSIZE+1],int);
void imprimir_tiempo();

void imprimir_punto_B(){
		char out[BUFFSIZE+1];
		char buffer[BUFFSIZE+1]; 
	
		//Fecha y hora actua
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
		lectura_archivo("/proc/version",buffer,0);
		printf("Version kernel: %s",buffer);
		imprimir_tiempo();
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
