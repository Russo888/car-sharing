#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "inserimento_dati.h"
#include "ricerche.h"
#include "gestione_valutazione.h"
#define DIM 100
//definizione di un tipo di dato per le flag
typedef enum{True, False}bool_t;

//Definizione di una struct per gestire meglio l'inserimento di una */
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

/**
 * Questa è la funzione che inserisce una nuova tratta nel file: calcola il codice univoco, chiede in
 * input i campi della tratta e una volta inseriti tutti, chiede conferma per salvare l'inserimento
 * mostrando i dati inseriti
*/
void inserisci_tratta(FILE *file_registro, FILE *file_valutazione)
{
	setvbuf(stdout,NULL,_IONBF,0);
	//definizioni delle variabili
	tratta viaggio;
    long  fileSize;
	char scelta[20];
	int scelta_int, posti_int, conta_viaggi_eliminati, appoggia_codice;

    fseek(file_registro, 0, SEEK_END);	// Sposta la posizione corrente alla fine del file
    fileSize = ftell(file_registro);	// Ottieni la dimensione del file
    //calcolo del codice univoco
    if(fileSize == 0)	// se filesize è uguale a 0, il file è vuoto
    {
    	viaggio.codice=1;
	}
    else
    {
    	conta_viaggi_eliminati=0;
    	rewind(file_registro);
        while (!feof(file_registro))
        {
        	fread(&viaggio, sizeof(tratta), 1, file_registro);
    	    if (!feof(file_registro))
    	    {
    	    	posti_int=atoi(viaggio.posti);
    	    	if(posti_int==0)
    	    	{
    	    		conta_viaggi_eliminati++;
    	    		appoggia_codice=viaggio.codice;
    	    	}
    	    }
    	}
        viaggio.codice=appoggia_codice;
        if(conta_viaggi_eliminati==0)
        {
        	fseek(file_registro, -sizeof(tratta), SEEK_END);
        	fread(&viaggio,sizeof(tratta),1,file_registro);
        	viaggio.codice++;
        }

    }

	//Inserimento dei dati
	puts("\n\n\n----------INSERIMENTO DI UNA NUOVA TRATTA----------");
	inserisci_nome(viaggio.nome);
	inserisci_cognome(viaggio.cognome);
	inserisci_partenza(viaggio.partenza);
	inserisci_arrivo(viaggio.arrivo);
	inserisci_data(viaggio.anno, viaggio.mese, viaggio.giorno);
	inserisci_posti(viaggio.posti);
	inserisci_costo(viaggio.costo);
	inserisci_note(viaggio.note);

	puts("\n------------------------------------------------------");
	puts("I dati inseriti per questo viaggio sono i seguenti:");
	printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
	printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
	puts("1)Salva.\n2)Ripeti l'inserimento.\n0)Torna al menu' guidatori senza salvare.");


	do
	{
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);

		switch(scelta_int)
		{
			case 1:
			{
				//Scrittura nel file
				if(conta_viaggi_eliminati==0)
				{
					fseek(file_registro,0, SEEK_END);
					fwrite(&viaggio, sizeof(tratta), 1, file_registro);
					aggiungi_al_file(viaggio.nome,viaggio.cognome, file_valutazione);
				}
				else
				{
					if (!feof(file_registro) && viaggio.codice!=0)
					{
						fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
						fwrite(&viaggio, sizeof(tratta), 1, file_registro);
						puts("saba");
						aggiungi_al_file(viaggio.nome,viaggio.cognome, file_valutazione);
						puts("saba");
					}
				}
			}break;
			case 2:
			{
				inserisci_tratta(file_registro, file_valutazione);
			}break;
			case 0:
			{
				}break;
			default:
			{
				puts("ERRORE, INSERIRE VALORE VALIDO");
			}
		}
	}while((scelta_int<0) | (scelta_int>2));
}

/**
 * Questa è la funzione che modifica la tratta dal file, prende in input un codice di una tratta e lo
 *  cerca nel file, se la trova chiede in input i nuovi campi della modifica e chiede conferma per
 *  salvare la modifica, mostrando i nuovi dati inseriti, in caso di conferma positiva la salva
*/
void modifica_tratta(int codice, FILE *file_registro)
{
	int scelta_int, posti_int;
	char scelta[20];
	setvbuf(stdout,NULL,_IONBF,0);
	tratta viaggio;
	rewind(file_registro);

	viaggio.codice=codice;

	fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
	fread(&viaggio, sizeof(tratta), 1, file_registro); //questa fread è necessaria per controllare che il record esista e sia avvalorato
	posti_int=atoi(viaggio.posti);
	if(posti_int!=0)
	{
		puts("----------------------------------------------------------------------");
		puts("La tratta da modificare e' questa:");
		printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
		printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
	}
	if (!feof(file_registro) && viaggio.codice!=0)
	{
		posti_int=atoi(viaggio.posti);
		if(posti_int!=0)
		{
			inserisci_nome(viaggio.nome);
			inserisci_cognome(viaggio.cognome);
			inserisci_partenza(viaggio.partenza);
			inserisci_arrivo(viaggio.arrivo);
			inserisci_data(viaggio.anno, viaggio.mese, viaggio.giorno);
			inserisci_posti(viaggio.posti);
			inserisci_costo(viaggio.costo);
			inserisci_note(viaggio.note);

			puts("--------------------------------------------------");
			puts("I dati inseriti per la modifica sono i seguenti:");
			printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
			printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
			puts("1)Salva la modifica.\n2)Ripeti l'inserimento.\n0)Torna al menu' guidatori senza salvare.");

			do
			{
				inserisci_scelta(scelta);
				scelta_int=atoi(scelta);

				switch(scelta_int)
				{
					case 1:
					{
						//Scrittura nel file
						fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET); //questa fseek è necessaria perchè dopo la fread il puntatore si è spostato
						fwrite(&viaggio, sizeof(tratta), 1, file_registro);
					}break;
					case 2:
					{
						modifica_tratta(viaggio.codice, file_registro);
					}break;
					case 0:
					{
						}break;
					default:
					{
						puts("ERRORE, INSERIRE VALORE VALIDO");
					}
				}
			}while((scelta_int<0) | (scelta_int>2));
		}
		else	puts("\n\n*********Codice non trovato*********");
	}
	else
		puts("\n\n*********Codice non trovato*********");
}

/**
 * Questa è la funzione che elimina la tratta dal file, prende in input un codice di una tratta e lo
 *  cerca nel file, se la trova chiede conferma per eliminare la tratta, in caso di conferma positiva,
 *  la elimina
*/
void elimina_tratta(int codice, FILE *file_registro)
{
	int scelta_int, posti_int;
	char scelta[20];
	setvbuf(stdout,NULL,_IONBF,0);
	tratta viaggio;
	rewind(file_registro);

	viaggio.codice=codice;

	fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET);
	fread(&viaggio, sizeof(tratta), 1, file_registro); //questa fread è necessaria per controllare che il record esista e sia avvalorato
	if (!feof(file_registro) && viaggio.codice!=0)
	{
		posti_int=atoi(viaggio.posti);
		if(posti_int!=0)
		{
			puts("---------------------------------------------------------------");
			puts("La tratta da eliminare e' questa:");
			printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
			printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
			puts("1)Elimina definitivamente.\n0)Torna al menu' guidatori senza eliminare.\n");
			do
			{
				inserisci_scelta(scelta);
				scelta_int=atoi(scelta);

				switch(scelta_int)
				{
					case 1:
					{
						//Scrittura nel file
						sprintf(viaggio.posti,"%d",0);
						fseek(file_registro,(viaggio.codice-1)*sizeof(tratta), SEEK_SET); //questa fseek è necessaria perchè dopo la fread il puntatore si è spostato
						fwrite(&viaggio, sizeof(tratta), 1, file_registro);
					}break;
					case 0:
					{
						}break;
					default:
					{
						puts("ERRORE, INSERIRE VALORE VALIDO");
					}
				}
			}while((scelta_int<0) | (scelta_int>2));
		}
		else	puts("\n\n*********Codice non trovato*********");
	}
	else
		puts("\n\n*********Codice non trovato*********");
}

/**
 * Questo è il menu utilizzato per far scegliere ai guidatori come ricercare la tratta da modificare:
 * 1)Modifica tratta con un codice
 * 2)Cerca tratta da modificare con il nome e il cognome
 * 0)Torna al menu' guidatori
*/
void menu_modifica(FILE *file_registro)
{
	int scelta_int, trovato, posti_int;
	setvbuf(stdout,NULL,_IONBF,0);
	tratta viaggio;
	char scelta[20];
	rewind(file_registro);
	do
	{
		puts("\n\n\n-----------MODIFICA TRATTA------------");
		puts("\n1)Modifica tratta con un codice.");
		puts("\n2)Cerca tratta da modificare con il nome e il cognome.");
		puts("\n0)Torna al menu' guidatori.");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);
		switch(scelta_int)
		{
			case 1:
			{
				puts("\nInserire il codice del viaggio che vuoi modificare-->");
				printf("\tCODICE --> " );
				scanf("%d", &viaggio.codice);
				modifica_tratta(viaggio.codice, file_registro);
			}break;

			case 2:{
				char cerca_nome[100], cerca_cognome[100];
								inserisci_nome(cerca_nome);
								inserisci_cognome(cerca_cognome);

								puts("-----------------------------------------------------------------");
								printf("\n%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
								rewind(file_registro);
								while (!feof(file_registro))
								{
									if (strstr(viaggio.nome,cerca_nome) && strstr(viaggio.cognome,cerca_cognome) != NULL)
									{
										posti_int=atoi(viaggio.posti);
										if(posti_int!=0)
										{
											trovato = 1;
											printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
										}
									}
								fread(&viaggio, sizeof(tratta), 1, file_registro);
								}
								if (!trovato) {
									puts ("*********Nome e cognome non trovati*********");
								}
								else
								{
									puts("\nInserire il codice del viaggio che vuoi modificare-->");
									printf("\tCODICE --> " );
									scanf("%d", &viaggio.codice);
									modifica_tratta(viaggio.codice, file_registro);
								}
				}break;
			case 0:
			{
			}break;
			default:{
				puts("ERRORE, INSERIRE UN DATO VALIDO");
			}
		}
	}while(scelta_int!=0);
}

/**
 * Questo è il menu utilizzato per far scegliere ai guidatori come ricercare la tratta da eliminare:
 * 1)Elimina tratta con un codice
 * 2)Cerca tratta da eliminare con il nome e il cognome
 * 0)Torna al menu' guidatori
*/
void menu_elimina_tratta(FILE* file_registro)
{
	int  scelta_int, trovato, posti_int;
	setvbuf(stdout,NULL,_IONBF,0);
	tratta viaggio;
	char scelta[20];
	rewind(file_registro);
	do
	{
		puts("\n\n\n------------ELIMINA TRATTA------------");
		puts("\n1)Elimina tratta con un codice.");
		puts("\n2)Cerca tratta da eliminare con il nome e il cognome.");
		puts("\n0)Torna al menu' guidatori.");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);
		switch(scelta_int)
		{
			case 1:
			{
				puts("\nInserire il codice del viaggio che vuoi eliminare:");
				printf("\tCODICE --> " );
				scanf("%d", &viaggio.codice);
				elimina_tratta(viaggio.codice, file_registro);
			}break;

			case 2:{
				char cerca_nome[100], cerca_cognome[100];
				inserisci_nome(cerca_nome);
				inserisci_cognome(cerca_cognome);
				printf("\n\n\n%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n\n", "Codice", "Nome", "Cognome", "Partenza", "arrivo", "Giorno", "Mese", "Anno", "costo","posti","note");
				rewind(file_registro);
				while (!feof(file_registro))
				{

					if (strstr(viaggio.nome,cerca_nome) && strstr(viaggio.cognome,cerca_cognome) != NULL)
					{
						posti_int=atoi(viaggio.posti);
						if(posti_int!=0)
						{
							trovato = 1;
							printf("%-10d %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", viaggio.codice, viaggio.nome, viaggio.cognome, viaggio.partenza, viaggio.arrivo, viaggio.giorno,viaggio.mese,viaggio.anno, viaggio.costo, viaggio.posti ,viaggio.note);
						}
					}
				fread(&viaggio, sizeof(tratta), 1, file_registro);
				}
				if (!trovato) {
					puts ("*********Nome e cognome non trovati*********");
				}
				else
				{
					puts("\nInserire il codice del viaggio che vuoi eliminare-->");
					printf("\tCODICE --> " );
					scanf("%d", &viaggio.codice);
					elimina_tratta(viaggio.codice, file_registro);
				}
				}break;
			case 0:
			{
			}break;
			default:{
				puts("ERRORE, INSERIRE UN DATO VALIDO");
			}
		}
	}while(scelta_int!=0);
}


/*
 * Questo è il menu utilizzato per far scegliere l'operazione da compiere ai guidatori, queste sono
 * le varie opzioni:
 * 1)Inserisci una nuova tratta
 * 2)Modifica una tratta esistente
 * 3)Cancellazione tratta
 * 0)Torna al menu' principale
*/
void menu_guidatore(FILE *file_registro, FILE *file_valutazione)
{
	setvbuf(stdout,NULL,_IONBF,0);
	char scelta[DIM];
	int scelta_int;
	do
	{
		puts("\n\n\n----------MENU' GUIDATORE----------");
		puts("\n1)Inserisci una nuova tratta.");
		puts("\n2)Modifica una tratta esistente.");
		puts("\n3)Cancellazione tratta.");
		puts("\n0)Torna al menu' principale.");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);

		switch(scelta_int)
		{
			case 1:{
				inserisci_tratta(file_registro, file_valutazione);
			}break;
			case 2:{
				menu_modifica(file_registro);
			}break;
			case 3:
			{
				menu_elimina_tratta(file_registro);
			}break;
			case 0:
			{
			}break;
			default:{
				puts("ERRORE, INSERIRE UN DATO VALIDO");
			}
		}
	}
	while(scelta_int!=0);
}
