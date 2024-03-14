#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "inserimento_dati.h"

#define DIM 100
/**Definizione di una struct per gestire meglio l'inserimento di una tratta*/
typedef struct{
	int codice;
	char nome[DIM];
	char cognome[DIM];
	char partenza[DIM];
	char arrivo[DIM];
	char mese[3];
	char giorno[3];
	char anno[5];
	char costo[10];
	char posti[10];
	char note[DIM];
}tratta;

/**Questa funzione ordina l'elenco dei risultati trovati nelle varie ricerche*/
void ordina_elenco(FILE *file_ord, int num_elementi)
{
	tratta viaggio, tmp;
    float costo_float1,costo_float2;
    long int posizione1, posizione2;
    int i=0, j=0;
    fseek(file_ord, -sizeof(tratta), SEEK_END);
    fread(&viaggio,sizeof(tratta),1,file_ord);
    rewind(file_ord);

    for(i=0; i<num_elementi; i++)
    {
    	posizione1=ftell(file_ord);
    	fread(&viaggio, sizeof(tratta), 1, file_ord);
    		for(j=0; j<num_elementi; j++)
    		{
					costo_float1=atof(viaggio.costo);
					posizione2=ftell(file_ord);
					fread(&tmp, sizeof(tratta), 1, file_ord);
					costo_float2=atof(tmp.costo);
					if(costo_float1>costo_float2)
					{
						fseek(file_ord,posizione1, SEEK_SET);
						fwrite(&tmp, sizeof(tratta), 1, file_ord);
						fseek(file_ord,posizione2, SEEK_SET);
						fwrite(&viaggio, sizeof(tratta), 1, file_ord);
						fseek(file_ord,posizione1, SEEK_SET);
						fread(&viaggio, sizeof(tratta), 1, file_ord);
						fseek(file_ord,posizione2, SEEK_SET);
					}
    		}
    		fseek(file_ord,posizione1+sizeof(tratta), SEEK_SET);
    }

    rewind(file_ord);
    puts("I dati memorizzati nel file sono i seguenti");
    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");    for(i=0; i<num_elementi; i++)
   //ci dovrebbe essere un for
    {
    	fread(&viaggio, sizeof(tratta), 1, file_ord);
    	if (!feof(file_ord))
    		printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
    }
}

/**In questa sezione si potrà effettuare la prenotazione del viaggio*/
void prenotazione(FILE *file_registro)
{
	tratta viaggio;
	int posti_int=0, posti_viaggio=0,scelta_int=0;
	char scelta[20],posti_char[DIM];
	do
	{
		puts("Vuole prenotare uno di questi viaggi visualizzati?(Inserire 1 per effettuare una prenotazione, 2 per non prenotare!)");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);
	}while(scelta_int<1 && scelta_int>2);

	if(scelta_int==2)
	{
		puts("Va bene, la riporto al menu'.");
	}
	else if(scelta_int==1)
	{
		puts("Inserire il codice del viaggio che e' visualizzato nel prima colonna!");
		printf("\tCODICE --> " );
		scanf("%d", &viaggio.codice);
		fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
		fread(&viaggio, sizeof(tratta), 1, file_registro);

		if (!feof(file_registro))
		{
			do
			{
				puts("Inserire il numero dei posti che si vuole prenotare: ");
				inserisci_posti(posti_char);
				posti_int=atoi(posti_char);
			}while(posti_int<1 && posti_int>300);
			posti_viaggio=atoi(viaggio.posti);
			if(posti_viaggio-posti_int<0)
			{
				puts("Hai inserito troppi posti rispetto a quelli disponibili!");
				puts("***********Prenotazione Annullata!***********");
			}
			else
			{
				posti_viaggio-=posti_int;
				sprintf(viaggio.posti,"%d",posti_viaggio);
				fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
				fwrite(&viaggio, sizeof(tratta), 1, file_registro);
				puts("Prenotazione effettuata con successo!");
			}

		}
		else
			puts("***********Non sono stati trovati viaggi con questo codice***********");

	}
}

/**Funzione che ricerca una tratta in base ad un codice fornito da tastiera*/
void ricerca_codice(FILE *file_registro)
{
	tratta viaggio;
	int posti_int=0;

	printf("------------Cerca viaggio per Codice------------\n\n");
	puts("\nInserisci il codice da cercare:");
	printf("\tCODICE --> " );
	scanf("%d", &viaggio.codice);
	rewind(file_registro);
	fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
	fread(&viaggio, sizeof(tratta), 1, file_registro);
	if (!feof(file_registro) && viaggio.codice!=0)
	{
		posti_int=atoi(viaggio.posti);
		if(posti_int!=0)
		{
			printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
			printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
			prenotazione(file_registro);
		}
		else
		{
			puts("***********Non sono stati trovati viaggi con questo codice***********");
		}


	}
	else
	puts("***********Non sono stati trovati viaggi con questo codice***********");
}


/**Funzione che ricerca una tratta in base alla partenza e all'arrivo*/
void ricerca_arrivo(FILE *file_registro, FILE *file_ord)
{
	tratta viaggio;
	int trovato=0,posti_int=0, num_elementi=0;
	char andata[100], ritorno[100];

	puts("------------Cerca viaggio per Partenza e Destinazione------------\n");
	inserisci_partenza(andata);
	inserisci_arrivo(ritorno);
	rewind(file_registro);
	rewind(file_ord);
	while (!feof(file_registro))
	{

		if (strstr(viaggio.partenza,andata) && strstr(viaggio.arrivo,ritorno) != NULL)
		{
			posti_int=atoi(viaggio.posti);
			if(posti_int!=0)
			{
				trovato = 1;
				fwrite(&viaggio, sizeof(tratta), 1, file_ord);
				num_elementi++;
			}
			else
			{
				puts("\n***********Destinazione non trovata\n");
			}

		}
	fread(&viaggio, sizeof(tratta), 1, file_registro);
	}
	if (!trovato) {
		puts ("\n***********Destinazione non trovata***********\n");
		}
	else
	{
		ordina_elenco(file_ord, num_elementi);
		prenotazione(file_registro);
	}
}

/**Funzione che ricerca una tratta in base alla partenza, all'arrivo e alla data*/
void ricerca_arrivo_data(FILE *file_registro, FILE *file_ord)
{
	tratta viaggio;
	int trovato=0, posti_int=0, num_elementi=0;
	char andata[100], ritorno[100], giorno[3], mese[3], anno[5];

	puts("------------Cerca viaggio per Partenza,Destinazione e data------------\n");
	inserisci_partenza(andata);
	inserisci_arrivo(ritorno);
	inserisci_data(anno, mese, giorno);

	rewind(file_registro);
	rewind(file_ord);
	while (!feof(file_registro))
	{
		if (strstr(viaggio.partenza,andata) && strstr(viaggio.arrivo,ritorno) && strstr(viaggio.anno,anno) && strstr(viaggio.mese,mese) && strstr(viaggio.giorno,giorno) != NULL)
		{
			posti_int=atoi(viaggio.posti);
			if(posti_int!=0)
			{
				trovato = 1;
				fwrite(&viaggio, sizeof(tratta), 1, file_ord);
				num_elementi++;
			}
			else
			{
				puts("\n***********Destinazione o data non trovata***********\n");
			}

		}
	fread(&viaggio, sizeof(tratta), 1, file_registro);
	}
	if (!trovato) {
		puts ("\n***********Destinazione o data non trovata***********\n");
	}
	else
		{
			ordina_elenco(file_ord, num_elementi);
			prenotazione(file_registro);
		}
}
