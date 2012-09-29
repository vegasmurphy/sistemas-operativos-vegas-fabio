#include "puntob.c"


void imprimir_idleTime();
void imprimir_UserTime();
void imprimir_System_Time();
void imprimir_cambios_contexto();
void imprimir_procesos();
void imprimir_Boot_time();

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
