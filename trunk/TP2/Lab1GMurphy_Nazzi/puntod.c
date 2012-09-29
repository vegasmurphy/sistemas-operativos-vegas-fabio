#include "puntoc.c"
void imprimir_info_memoria();
void imprimir_lista_promedio_cargas();
void imprimir_peticiones_disco();
void imprimir_punto_C();

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
				acumulador += atoi(buffer+18);
				int espacios=0;
				int i=0;
				
				while(espacios<2){
					if (*(buffer+18+i)==' ')
						{espacios++;}
					i++;
				}
				
				acumulador+=atoi(buffer+18+i);
				//printf("%i \n",atoi(buffer+17+i));
				//printf("%i \n",acumulador);
				strcpy(lectura[i],buffer);
				
			}
			i=i+1;
		}
		
		printf("Peticiones a Disco: %i \n",acumulador);
	
		fclose(fd);
}


