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

int main(int argc, char *argv[]) 
{ 	
	char out[BUFFSIZE+1];
	char buffer[BUFFSIZE+1]; 
	
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
	
	//imprimir_tiempo();
	/*Punto C. Imprime con -s 
	 * los datos solicitados
	 * */
	if(argc>1){
		if(!strcmp(argv[1],"-s")){
			imprimir_idleTime();
			imprimir_UserTime();
			imprimir_System_Time();
			imprimir_cambios_contexto();
			imprimir_procesos();
			imprimir_Boot_time();
		}
	}
	
	/*
	 * Punto D todas las llamadas a funciones van dentro del bucle for el cual lo
	 * imprime con el retardo correspondiente
	 */
	if (argc==4){											//Pregunta si la cantidad de parametros que recibe 'main' es 4
		if(!strcmp(argv[1],"-l")){							//Pregunta si el parametro ubicado en la posicion 1 del argv[] es'-l'
			int i=0;
			
			imprimir_idleTime();
			imprimir_UserTime();
			imprimir_System_Time();
			imprimir_cambios_contexto();
			imprimir_procesos();
			imprimir_Boot_time();
			
			for (i=0;i<atoi(argv[3])/ atoi(argv[2]);i++){
				
				//Aca van las llamadas a funciones
				imprimir_info_memoria();
				imprimir_lista_promedio_cargas();
				
				
			//	printf("delay %i \n",atoi(argv[2]));
				sleep(atoi(argv[2]));
			}
		}
	}
	
	return 0;
}

 
/*lee el archivo y imprime las lineas pasadas en un arreglo
 * recibe como parametro un arreglo el cual contiene en 
 * primer lugar la cantidad de datos del arreglo
*/

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

void imprimir_tiempo()
{
	FILE *fd;
	fd= fopen("/proc/uptime","r");
	int i=0;
	
	char buffer[BUFFSIZE+1]; 
	fgets(buffer,BUFFSIZE+1,fd);
	for (i=0;i<BUFFSIZE+1;i++){
		if (buffer[i]==' ')
		{break;}
		}
		char salida[i];
		strcpy(salida,buffer);
		float s;
		s=atof(salida);
	fclose(fd);
	
	int ss;
	ss=(int)s;
	int dias,horas,minutos,segundos;
	dias= ss/(86400);
	horas=(ss % 86400)/3600;
	minutos=(ss % 3600)/60;
	segundos=(ss % 60);
	printf("Uptime: %iD:%iH:%iM:%iS \n",dias,horas,minutos,segundos);
	
	}

void imprimir_idleTime()
{	FILE *fd;
	fd= fopen("/proc/uptime","r");
	int i=0;
	
	char buffer[BUFFSIZE+1]; 
	fgets(buffer,BUFFSIZE+1,fd);
	for (i=0;i<BUFFSIZE+1;i++){
		if (buffer[i]==' ')
		{break;}
		}
		char salida[100];
		strcpy(salida,buffer+i);
		float s;
		s=atof(salida);
	fclose(fd);
	
	int ss;
	ss=(int)s;
	int dias,horas,minutos,segundos;
	dias= ss/(86400);
	horas=(ss % 86400)/3600;
	minutos=(ss % 3600)/60;
	segundos=(ss % 60);
	printf("Idle Time: %iD:%iH:%iM:%iS \n",dias,horas,minutos,segundos);
	}

void imprimir_UserTime(){
	FILE *fd;
	fd= fopen("/proc/stat","r");
	int i=0;
	
	char buffer[BUFFSIZE+1]; 
	fgets(buffer,BUFFSIZE+1,fd);
	for (i=0;i<BUFFSIZE+1;i++){
		if (buffer[i]==' ')
		{break;}
	}
	char salida[100];
	strcpy(salida,buffer+i);
	float s;
	s=atof(salida);
	fclose(fd);
	
	int ss;
	ss=(int)s/100;
	int dias,horas,minutos,segundos;
	dias= ss/(86400);
	horas=(ss % 86400)/3600;
	minutos=(ss % 3600)/60;
	segundos=(ss % 60);
	printf("User Time: %iD:%iH:%iM:%iS \n",dias,horas,minutos,segundos);
}
	
void imprimir_System_Time(){
	FILE *fd;
	fd= fopen("/proc/stat","r");
	int i=0;
	
	char buffer[BUFFSIZE+1]; 
	fgets(buffer,BUFFSIZE+1,fd);
	int espacios=0;
	for (i=0;i<BUFFSIZE+1;i++){
		if (buffer[i]==' ')
		{
			espacios++;
			if (espacios==3){break;}
		}
	}
	char salida[100];
	strcpy(salida,buffer+i);
	float s;
	s=atof(salida);
	fclose(fd);
	
	int ss;
	ss=(int)s/100;
	int dias,horas,minutos,segundos;
	dias= ss/(86400);
	horas=(ss % 86400)/3600;
	minutos=(ss % 3600)/60;
	segundos=(ss % 60);
	printf("System Time: %iD:%iH:%iM:%iS \n",dias,horas,minutos,segundos);
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

void imprimir_Boot_time(){
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
	
void imprimir_procesos(){
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
