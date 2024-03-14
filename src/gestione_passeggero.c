/*
 * gestione_passeggero.c
 *
 *      Author: Francescopio Scarale e Nicola Russo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "ricerche.h"
#include "inserimento_dati.h"
#include "gestione_valutazione.h"
#define DIM 100
typedef enum{True, False}bool_t;

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

FILE *valutazione;
/**questo è il menù per effettuare la ricerca, dove ci sono 3 tipi di ricerche,
 * la prima ricerca avviene inserendo il luogo di partenza e il luogo di arrivo
 * la seconda ricerca, invece avviene inserendo il luogo di partenza, l arrivo e in piu anche la data
 * la terza ricerca avviene inserendo il codice del viaggio e della tratta
 * una volta terminata la ricerca, se sono visualizzati viaggi uscirà un opzione per prenotare un viaggio oppure no
 *
 */
void menu_ricerca(FILE *file_registro, FILE *file_ord)
{
		char scelta[20];
		char scelta_int;
		do
		{
			puts("\n----------MENU' RICERCHE----------");
			puts("\n1)Ricerca Viaggio per partenza e arrivo");
			puts("\n2)Ricerca viaggio per partenza, arrivo e data.");
			puts("\n3)Ricerca viaggio per codice.");
			puts("\n0)Per tornare al menu' passeggeri.");
			inserisci_scelta(scelta);
			scelta_int=atoi(scelta);

			switch(scelta_int)
			{
				case 1:
				{
					ricerca_arrivo(file_registro, file_ord);
				}break;
				case 2:
				{
					ricerca_arrivo_data(file_registro, file_ord);
				}break;
				case 3:
				{
					ricerca_codice(file_registro);
				}break;
				case 0:
				{

				}break;
				default:
				{
					puts("ERRORE, INSERIRE VALORE VALIDO");
				}
			}
		}while(scelta_int!=0);

}
/**Menu del passeggere, in questa sezione il passeggero dovrà scegliere tra le seguenti opzioni
*1)per ricercare un viaggio, e poi nella stessa sezione,una volta trovato il viaggio, il programma chiedera se il passeggero vorrà prenotare il viaggio che ha appena ricercato
*2)in questa sezione il passeggero valuterà un guidatore inserendo un voto da 1 a 10
*3)in questa sezione, invece, sarà visualizzato il guidatore con la media dei voti piu alta di tutti
*0)in questa sezione si torna al menu principale*/
void menu_passeggero(FILE *file_registro,  FILE *file_valutazione, FILE *file_ord)
{
	char scelta[20];
	char scelta_int;
	do
	{
		puts("\n----------MENU' PASSEGGERO----------");
		puts("\n1)Ricerca Viaggio.");
		puts("\n2)Valutazione Guidatore.");
		puts("\n3)Visualizzazione migliori guidatori");
		puts("\n0)Per tornare al menu' principale");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);

		switch(scelta_int)
		{
			case 1:
			{
				menu_ricerca(file_registro, file_ord);
			}break;
			case 2:
			{
				inserimento_valutazione( file_valutazione);
			}break;
			case 3:
			{
				miglior_guidatore(file_valutazione);
			}break;
			case 0:
			{

			}break;
			default:
			{
				puts("ERRORE, INSERIRE VALORE VALIDO");
			}
		}
	}while(scelta_int!=0);
}
