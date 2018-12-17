#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

time_t time(time_t *__timer){//@override
	if(__timer){
		*__timer =(time_t)(*__timer);
	}
	return *__timer;
}

int main(){

	time_t massimo=2147483647;//numero di secondi fino al 19 gennaio 2038
	time_t n=0,sec;
	
	int giorno=1;

	char * data;

	pid_t ID;
	
	FILE *fd;


	while(n<massimo&&giorno<=24855){
		

		sec=time(&n);
		data= ctime(&sec);
	

		/* apre il file in scrittura */
		fd=fopen("nascondi-time-mod.c", "w");

		if( fd==NULL ) {
			perror("Errore in apertura del file");
			exit(1);
		}
		//riscrivo ogni volta il file nascondi time mod con i secondi modificati
		fprintf(fd,"%s", "#include <time.h>\n\ntime_t time(time_t *__timer){\nif(__timer){\n*__timer =(time_t)");
		fprintf(fd,"%ld",n);
		fprintf(fd,"%s\n",";");
		fprintf(fd,"%s\n","}");
		fprintf(fd,"%s","return ");
		fprintf(fd,"%ld",n);
		fprintf(fd,"%s\n",";");
		fprintf(fd,"%s\n","}");

		fclose(fd);

		ID=fork();

		if(ID==-1){
			puts("errore nella fork");
			exit(1);
		}
		if(ID==0){
			execlp("./lancio_preload.sh","",NULL);
			printf("exec fallita");
		}
		if(ID!=0){
			wait(NULL); //sono il padre ed aspetto il figlio
		}
		n+=86400;giorno++;
	}//fine while

}//fine main
