
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date{
    int month;
    int day;
    int year;
    int ore,minuti,secondi;
};

int number_of_days (struct date data);
int numeroMese(char  * mese);
int giorniMese(int mese, int anno);
int bisestile(int anno);

time_t time(time_t *__timer){//@override
	if(__timer){
		*__timer =(time_t)(*__timer);
	}
	return *__timer;
}


int main(){
	
	FILE *fd;

	/* apre il file in scrittura */
	fd=fopen("outputCorretto.txt", "w");

	if( fd==NULL ) {
		perror("Errore in apertura del file");
		exit(1);
	}


	time_t massimo=2147483647;//numero di secondi fino al 19 gennaio 2038
	time_t n=0,sec;

	char * data,*token;
	char * pezzi[7]={};
	

	int i,number1,number2;

	struct date data1, data2;

	int giorno=1;
	//24855 è numero di giorni dal 1 gennaio 1970 al 19 gennaio 2038


	while(n<massimo&&giorno<=24855){

		sec=time(&n);
		//printf("time=%d\n",sec);
		//fprintf(fd, "%d\n",sec);

		data= ctime(&sec);
		//printf("data corrispondente ai sec:%s\n",data);
		fprintf(fd,"%s", "data corrispondente ai sec: ");
		fprintf(fd, "%s",data);


	
    	token = strtok(data, " :");
    	
		//printf("%s\n",token);
	
    	i=0;
	
    	while( token != NULL && i<7){
			pezzi[i]=token;
    	    token = strtok(NULL, " :");
    	    //printf( " pezzo %d-esimo: %s\n", i, pezzi[i] );
    	    i++;
    	}
		
    	data1.month=numeroMese(pezzi[1]);
		data1.day=atoi(pezzi[2]);
		data1.ore=atoi(pezzi[3]);
		data1.minuti=atoi(pezzi[4]);
		data1.secondi=atoi(pezzi[5]);
		data1.year=atoi(pezzi[6]);
	

		data2.month=numeroMese(pezzi[1]);

		data2.day=giorniMese(data1.month,data1.year);

		data2.ore=atoi(pezzi[3]);
		data2.minuti=atoi(pezzi[4]);
		data2.secondi=atoi(pezzi[5]);
		data2.year=atoi(pezzi[6]);

    	number1 = number_of_days(data1);
	    number2 = number_of_days(data2);//imposto all'ultimo giorno del mese ogni volta

    	//printf("numero di giorni rimanenti è: %i\n", number2 - number1);
		fprintf(fd,"%s","numero dei giorni rimanenti è: ");
		fprintf(fd, "%d\n", number2-number1);

		//n+=1; NON VADO AVANTI DI SECONDO IN SECONDO MA..
		n+=86400; //vado al giorno dopo: 86400 è il num di secondi in un giorno.
		giorno+=1;
	}

	//chiudo il file
	fclose(fd);
    return 0;

}


int number_of_days (struct date data){
    int number;

    if (data.month <= 2)
        number = (1461 * (data.year - 1)) / 4 + (153 * (data.month + 13)) / 5 + data.day;
    else
        number = (1461 * data.year) / 4 + (153 * (data.month + 1)) / 5 + data.day;

    return number;
}//fine numero giorni

int numeroMese(char  * mese){
	if(strcmp(mese,"Jan")==0) return 1;
	if(strcmp(mese,"Feb")==0) return 2;
	if(strcmp(mese,"Mar")==0) return 3;
	if(strcmp(mese,"Apr")==0) return 4;
	if(strcmp(mese,"May")==0) return 5;
	if(strcmp(mese,"Jun")==0) return 6;
	if(strcmp(mese,"Jul")==0) return 7;
	if(strcmp(mese,"Aug")==0) return 8;
	if(strcmp(mese,"Sep")==0) return 9;
	if(strcmp(mese,"Oct")==0) return 10;
	if(strcmp(mese,"Nov")==0) return 11;
	if(strcmp(mese,"Dec")==0) return 12;
}

int giorniMese(int mese, int anno){

	if(mese==4|| mese==11 || mese==6 || mese ==9){ return 30;}

	if(mese==2){
		if( ((anno % 4 == 0 && anno % 100 != 0)||anno % 400 == 0)) { return 29;}
		else{ return 28; }
	}
	return 31;
}

