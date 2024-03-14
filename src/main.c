/*
 ============================================================================
 Name        : ScaraleFrancescopio_RussoNicola_CarSharing.c
 Author      : Francescopio_Nicola
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_guidatore.h"
#include "gestione_passeggero.h"
#include "inserimento_dati.h"
/*
 * Lunghezza massima utilizzata per le stringhe
 */

/**
 * Funzione principale.
 * Mostra il primo menu' per controllare se sei un guidatore o un passeggere, o terminare l'esecuzione del programma
 *
 * @return 0
 */

int main(void) {
	setvbuf(stdout,NULL,_IONBF,0);

	FILE *registro;
	registro=fopen("registro_viaggi.bin", "rb+");
	if (registro==NULL)
	      printf("\n\n\n*********** Impossibile aprire il file registro_viaggi.bin************* \n\n");

	FILE *valutazione;
	valutazione=fopen("valutazioni.bin", "rb+");
		if (valutazione==NULL)
		      printf("\n\n\n*********** Impossibile aprire il file valutazioni.bin************* \n\n");

	FILE *file_ord;
	file_ord=fopen("elenco_ordinato.bin", "rb+");
		if (file_ord==NULL)
		      printf("\n\n\n*********** Impossibile aprire il file elenco_ordinato.bin************* \n\n");



	char scelta[20];
	int scelta_int;
	do
	{
		puts("\tBENVENUTO AL SERVIZIO CARSHARING");
		puts("\n----------MENU' PRINCIPALE----------");
		puts("\n1)Se sei un guidatore.");
		puts("\n2)Se sei un passeggero.");
		puts("\n0)Uscita.");
		inserisci_scelta(scelta);
		scelta_int=atoi(scelta);


		switch(scelta_int)
		{
			case 1:
			{
				menu_guidatore(registro, valutazione);
			}break;
			case 2:
			{
				menu_passeggero(registro, valutazione, file_ord);
			}break;
			case 0:
			{
				puts("\nARRIVEDERCI");
			}break;
			default:{
				puts("\nERRORE, INSERIRE UN DATO VALIDO");
			}
		}

	}while(scelta_int!=0);
	fclose(registro);
	fclose(valutazione);
	fclose(file_ord);
	system("pause");
	return 0;
}
