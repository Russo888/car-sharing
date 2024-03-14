/*
 * gestione_passeggero.c
 *
 *      Author: Francescopio Scarale e Nicola Russo
 */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum{True, False}bool_t;
#define DIM 100

/** Funzione che porta tutte le parole di una stringa ad avere la prima lettera maiuscola ed
 * il resto minuscole
 */
void maiueminu(char *s)
{
	int i;
    for (i=0; i<strlen(s); i++)
    {
    	if(i==0)
         if ((s[i]>='a') && (s[i]<='z'))
        	 s[i]-=32;
    	if(i!=0)
    	{
    		if(s[i-1]==' ')
    			if ((s[i]>='a') && (s[i]<='z'))
    				s[i]-=32;
    		if(s[i-1]!=' ')
    			if ( (s[i]>='A') && (s[i]<='Z') )
    				s[i]+=32;
    	}

    }
}

/** Rimozione del carattere di nuova linea alla fine della stringa*/
void rimuovi_accapo(char string[100])
{
		size_t len = strlen(string);
		if (len > 0 && string[len-1] == '\n')
		{
			string[len-1] = '\0';
		}
}

/** Funzione che fa inserire una scelta per i menu e fa i vari controlli*/
void inserisci_scelta(char scelta[20])
{
	bool_t flag;
	size_t len;
	int i;
	do
		{
			fflush(stdin);
			flag=False;
			puts("\nInserisci la tua scelta: ");
			printf("\tSCELTA --> " );
			fgets(scelta, 20, stdin);
			rimuovi_accapo(scelta);
			len = strlen(scelta);
			if(len==0) flag=True;
			for(i=0; i<strlen(scelta); i++)
			{
				if(isdigit(scelta[i])==0)	flag=True;
			}
		}while(flag==True);
}

/**Funzione che fa inserire un nome*/
void inserisci_nome(char nome[DIM])
{
	fflush(stdin);
	size_t len;
	puts("\nInserisci il nome del guidatore");
	printf("\tNOME --> " );
	fgets(nome, DIM, stdin);
	rimuovi_accapo(nome);
	len = strlen(nome);
	if(len==0) inserisci_nome(nome);
	maiueminu(nome);
}

/**Funzione che fa inserire un cognome*/
void inserisci_cognome(char cognome[DIM])
{
	fflush(stdin);
	size_t len;
	puts("\nInserisci il cognome del guidatore");
	printf("\tCOGNOME --> " );
	fgets(cognome, DIM, stdin);
	rimuovi_accapo(cognome);
	len = strlen(cognome);
	if(len==0) inserisci_cognome(cognome);
	maiueminu(cognome);
}

/**Funzione che fa inserire una partenza*/
void inserisci_partenza(char partenza[DIM])
{
	fflush(stdin);
	size_t len;
	puts("\nInserisci la partenza");
	printf("\tPARTENZA --> " );
	fgets(partenza, DIM, stdin);
	rimuovi_accapo(partenza);
	len = strlen(partenza);
	if(len==0) inserisci_partenza(partenza);
	maiueminu(partenza);
}

/**Funzione che fa inserire un arrivo*/
void inserisci_arrivo(char arrivo[DIM])
{
	fflush(stdin);
	size_t len;
	puts("\nInserisci l'arrivo");
	printf("\tARRIVO --> " );
	fgets(arrivo, DIM, stdin);
	rimuovi_accapo(arrivo);
	len = strlen(arrivo);
	if(len==0) inserisci_arrivo(arrivo);
	maiueminu(arrivo);
}

/**Funzione che fa inserire una data con tutti i controlli*/
void inserisci_data(char anno[5], char mese[3], char giorno[3])
{
	int giorno_int, mese_int, anno_int, giorno_corrente, mese_corrente, anno_corrente;
	bool_t flag;
	time_t now;
	size_t len;
	time(&now);

	// localtime converte un valore `time_t` nell'ora del calendario e
		// restituisce un puntatore a una struttura `tm` con i suoi membri
		// riempito con i valori corrispondenti
		struct tm *local = localtime(&now);

		giorno_corrente = local->tm_mday;            // ottieni il giorno del mese (da 1 a 31)
		mese_corrente = local->tm_mon + 1;      // ottieni il mese dell'anno (da 0 a 11)
		anno_corrente = local->tm_year + 1900;   // ottieni l'anno dal 1900


	puts("\nInserisci la data di partenza:");
	puts("Inserisci l'anno(verranno presi in considerazione solo i primi 4 numeri inseriti)");
		do
		{
			fflush(stdin);
			flag=False;
			printf("\tANNO --> " );
			fgets(anno, 5, stdin);
			rimuovi_accapo(anno);
			len = strlen(anno);
			if(len==0) flag=True;
			anno_int=atoi(anno);
			if (anno_int < anno_corrente)	flag=True;
		}while(flag ==True);

		puts("\nInserisci il mese(verranno presi in considerazione solo i primi 2 numeri)");
		do
		{
			fflush(stdin);
			flag=False;
			printf("\tMESE --> " );
			fgets(mese, 3, stdin);
			rimuovi_accapo(mese);
			len = strlen(mese);
			if(len==0) flag=True;
			anno_int=atoi(anno);
			mese_int=atoi(mese);
			if(mese_int>12)	flag=True;
			if(mese_int<1) flag=True;
			if(anno_int==anno_corrente && mese_int<mese_corrente) flag=True;
		}while(flag==True);

		puts("\nInserisci il giorno(verranno presi in considerazione solo i primi 2 numeri)");
		do
		{
			fflush(stdin);
			flag=False;
			printf("\tGIORNO --> " );
			fgets(giorno, 3, stdin);
			rimuovi_accapo(giorno);
			len = strlen(giorno);
			if(len==0) flag=True;
			giorno_int=atoi(giorno);

			if(anno_int==anno_corrente)
			{
				if(mese_int==mese_corrente)
				{
					if(giorno_int<giorno_corrente)	flag=True;
				}
			}
			if(giorno_int<1)	flag=True;
			if((mese_int==4) & (giorno_int>30))    	flag=True;
			if((mese_int==6) & (giorno_int>30))   	flag=True;
			if((mese_int==9) & (giorno_int>30))    	flag=True;
			if((mese_int==11) & (giorno_int>30))    flag=True;
			if((mese_int==1) & (giorno_int>31))    	flag=True;
			if((mese_int==3) & (giorno_int>31))    	flag=True;
			if((mese_int==5) & (giorno_int>31))    	flag=True;
			if((mese_int==7) & (giorno_int>31))    	flag=True;
			if((mese_int==12) & (giorno_int>31))    flag=True;
			if((mese_int==2) & (giorno_int>28))
			{
				flag=True;
				if((giorno_int==29) & (anno_int%4==0))
				{
					flag=False;
				}
				if((giorno_int==29) & (anno_int%100==0))
				{
					flag=True;
					if(anno_int%400==0)
					{
						flag=False;
					}
				}
			}
		}while(flag==True);
}

/**Funzione che fa inserire il numero di posti*/
void inserisci_posti(char posti[10])
{
	bool_t flag;
	size_t len;
	int posti_int, i;
	puts("\nInserisci il numero di posti: ");
	do
		{
			fflush(stdin);
			flag=False;
			printf("\tPOSTI --> " );
			fgets(posti, 10, stdin);
			rimuovi_accapo(posti);
			len = strlen(posti);
			if(len==0) flag=True;
			posti_int=atoi(posti);
			for(i=0; i<strlen(posti); i++)
			{
				if(isdigit(posti[i])==0)	flag=True;
			}
			if(posti_int<1)		flag=True;
			if(posti_int>7)	flag=True;
		}while(flag==True);
}

/**Funzione che fa inserire il costo*/
void inserisci_costo(char costo[10])
{
	float costo_float;
	int i, cont_punti;
	bool_t flag;
	size_t len;
	puts("\nInserisci il costo eventualmente separando gli euro e i centesimi con un \".\"");
	do
	{
		fflush(stdin);
		cont_punti=0;
		flag=False;
		printf("\tPREZZO --> " );
		fgets(costo, 10, stdin);
		rimuovi_accapo(costo);
		len = strlen(costo);
		if(len==0) flag=True;
		costo_float=atof(costo);
		for(i=0; i<strlen(costo); i++)
		{
			if(isdigit(costo[i])==0)	flag=True;
			if(costo[i]=='.')
			{
				cont_punti++;
				if(cont_punti==1)
				{
					flag=False;
				}
				if((i==0)||(i==strlen(costo)-1))
				{
					flag=True;
				}
			}
		}
		if(costo_float<0)	flag=True;
	}while(flag==True);
}

/**Funzione che fa inserire le eventuali note*/
void inserisci_note(char note[DIM])
{
	puts("\nInserisci eventuali note");
	printf("\tNOTE --> " );
	fgets(note, DIM, stdin);
	rimuovi_accapo(note);

}






