
#include "AtenderRutas.c"

void Atender_Comando(char* comando[5]){	


   pid_t pID = vfork();

   if (pID == 0)                // child

   {

      // Code only executed by child process
		//printf("llego");
	char *path;
	int i=0;
	path=getenv("PATH");
	int flag=0;
	while((path[i]!='\0')||(flag==1)) {
		if(path[i]==':'){
			char temp[BUFFSIZE];
			int j;
			for(j=0;j<BUFFSIZE;j++) temp[j]='\0';
			strncpy(temp,path,i);
			//printf("%s\n",temp);
			strcat(temp,"/");
			strcat(temp,comando[0]);
			//printf("%s\n",temp);

			if(execv(temp,comando)!=-1){
				flag=1;
				//printf("se ejecuto\n");
				break;
				}
			strcpy(path,path+i+1);
			//printf("%s\n",path);
			i=0;
			}
		i++;
		
		
		}
		

      
     

      exit(0);

    }

    else if (pID < 0)            // failed to fork

    {

        

        exit(1);

        // Throw exception

    }

    else                                   // parent

    {
		wait(0);
      // Code only executed by parent process

 

      

	}	




}
