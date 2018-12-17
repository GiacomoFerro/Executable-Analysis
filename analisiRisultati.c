#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkMatchDate(char * data1, char * data2, FILE *fdMatch, FILE * fdMismatch);
int numeroMese(char * mese);

int main(){

	FILE * fdCorretto;
	FILE * fdErrato;
	FILE * fdFinal;
	FILE * fdMatch;
	FILE * fdMismatch;


	char bufCorretto[200];
	char bufErrato[200];


	char * rigaData1=NULL;
	char * rigaData2=NULL;
	char * data2=NULL;

	char * giorniCorretti=NULL;
	char * giorniErrati=NULL;

	char * token;
	char * pezziCorretti[2];
	char * pezziErrati[2];
	
	int i;

	fdCorretto=fopen("outputCorretto.txt", "r");
	fdErrato=fopen("outputGGFM.txt","r");
	fdFinal=fopen("confronto.txt", "w");
	fdMatch=fopen("matchDate.txt", "w");
	fdMismatch=fopen("misMatchDate.txt","w");

	if( fdCorretto == NULL || fdErrato == NULL || fdFinal == NULL|| fdMatch==NULL || fdMismatch==NULL) {
		perror("Errore in apertura dei file");
		exit(1);
	}


	while(1) {
		rigaData1=fgets(bufCorretto, 200, fdCorretto);
		if( rigaData1==NULL ){ break;}
		rigaData2=fgets(bufErrato, 200, fdErrato);
		if( rigaData2==NULL ){ break;}

		//AGGIUNGI CONTROLLO DATA
		checkMatchDate(rigaData1, rigaData2, fdMatch,fdMismatch);
		
		
		data2=malloc(sizeof(char)*200);	//faccio la copia per salvare la data 
		strcpy(data2,rigaData2);

		//leggo la riga dei giorni nei files
		giorniCorretti=fgets(bufCorretto, 200, fdCorretto);
		if( giorniCorretti==NULL ){ break;}
		giorniErrati=fgets(bufErrato, 200, fdErrato);
		if( giorniErrati==NULL ){ break;}	

		//pezzi corretti
		token = strtok(giorniCorretti, ":");
    	i=0;
	
    	while( token != NULL) {
			pezziCorretti[i]=token;
    	    token = strtok(NULL, ":");
    	    i++;
    	}
		//pezzo 2 contiene il numero

		//pezzi errati
		token = strtok(giorniErrati, ":");
    	i=0;
	
    	while( token != NULL) {
			pezziErrati[i]=token;
    	    token = strtok(NULL, ":");
    	    i++;
    	}

		;
		if(strcmp(pezziCorretti[1],pezziErrati[1]) != 0 ){ //se il giorni sono diversi scrivo su file	
			char datadbg[30]={};
			int j=0;
			while(*(data2)!='\n'){
				datadbg[j]=*data2;
				data2++;j++;
			}//tolgo \n nella data !! che è brutto nella stampa

			fprintf(fdFinal, "%s---> ", datadbg);
			fprintf(fdFinal, "%d vs ", atoi(pezziErrati[1]));
			fprintf(fdFinal, "(%d)\n\n", atoi(pezziCorretti[1]));
			
		}

  	}//fine while

	fclose(fdCorretto);
	fclose(fdErrato);
	fclose(fdFinal);
	fclose(fdMatch);
	fclose(fdMismatch);
}//fine main


void checkMatchDate(char * data1, char * data2, FILE *fdMatch, FILE * fdMismatch){
	
	char * token;
	char copia[20];
	char * pezziCorretti[20]={};	
	int i=0;

	token = strtok(data1, " :");
	
    while( token != NULL){
		pezziCorretti[i]=token;
        token = strtok(NULL, " :");
        //printf( " pezzo %d-esimo: %s\n", i, pezziCorretti[i] );
        i++;
    }

	char * pezziErrati[5]={};	
	i=0;	

	strcpy(copia,data2);
	token = strtok(copia, "-");

	
    while( token != NULL){
		pezziErrati[i]=token;
        token = strtok(NULL, " -");
        //printf( " pezzo %d-esimo: %s\n", i, pezziErrati[i] );
        i++;
    }

	//dati i pezzi delle date controllo la data!
	int mese=numeroMese(pezziCorretti[5]);
	int giorno=atoi(pezziCorretti[6]);
	int anno=atoi(pezziCorretti[10]);

	int mese2=atoi(pezziErrati[1]);
	int giorno2=atoi(pezziErrati[0]);//GIORNO è il primo campo
	int anno2=atoi(pezziErrati[2]);

	if( (mese==mese2) && (giorno==giorno2) && (anno==anno2) ){
		//caso match tra date...
		//printf("MATCH: %d/%d/%d e (%d/%d/%d) \n",giorno,mese,anno,giorno2,mese2,anno2);
		fprintf(fdMatch, "%s %d/%d/%d e (%d/%d/%d) \n","MATCH: ",giorno,mese,anno,giorno2,mese2,anno2);
		return;
	}
	else{
		//printf("MISMATCH: %d/%d/%d e (%d/%d/%d) \n",giorno,mese,anno,giorno2,mese2,anno2);
		fprintf(fdMismatch, "%s %d/%d/%d e (%d/%d/%d) \n","!!!!!MISMATCH!!!!!: ",giorno,mese,anno,giorno2,mese2,anno2);
		return;
	}
}

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




