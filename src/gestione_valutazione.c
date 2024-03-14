#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"inserimento_dati.h"

typedef enum{True, False}bool_t;	//definizione di un tipo di dato per le flag
#define DIM 100
typedef struct
	{
		int codice;
		char nome_guidatore[DIM];
		char cognome_guidatore[DIM];
		char valuta[DIM];
		float media;
		int cont_persone;
	}val_guidatore;
/**
 * in questa sezione si aggiungono al file binario delle valutazioni i nomi di tutti
 * i guidatori disponibili.
 */
void aggiungi_al_file(char nome[DIM], char cognome[DIM], FILE *file_valutazione)
{
		val_guidatore guidatore;
		long fileSize;
		int trovato=0;

		fseek(file_valutazione, 0, SEEK_END);					// Sposta la posizione corrente alla fine del file
		fileSize = ftell(file_valutazione);						// Ottieni la dimensione del file
		if(fileSize == 0)										// se filesize è uguale a 0, il file è vuoto
		{
			guidatore.codice=1;
		}
		else
		{
			fread(&guidatore, sizeof(val_guidatore), 1, file_valutazione);
			while (!feof(file_valutazione) && trovato == 0)
			{
				if (strcmp(guidatore.nome_guidatore, nome) == 0 && strcmp(guidatore.cognome_guidatore, cognome) == 0)
				{
					trovato = 1;
				}
				fread(&guidatore, sizeof(val_guidatore), 1, file_valutazione);
			}
			fseek(file_valutazione, -sizeof(val_guidatore), SEEK_END);
			fread(&guidatore,sizeof(val_guidatore),1,file_valutazione);
			guidatore.codice++;
		}

		if(trovato==0)
		{
			fseek(file_valutazione, 0, SEEK_END);
			guidatore.cont_persone=0;
			guidatore.media=0;
			guidatore.valuta[0]='0';
			strcpy(guidatore.nome_guidatore,nome);
			strcpy(guidatore.cognome_guidatore,cognome);
			fwrite(&guidatore, sizeof(val_guidatore),1,file_valutazione);
		}

}
/**
 * in questa sezione viene aggiunto la vlutazione del guidatore inserito dal passeggero
 * e poi viene calcolata la media totale
 */
void inserimento_valutazione(FILE *file_valutazione)
{
    bool_t flag=True;
    val_guidatore guidatore;
    val_guidatore tmp;
    int val_int=0,trovato=0,i=0,cont=0;
    char nome[DIM],cognome[DIM];

    inserisci_nome(nome);
    inserisci_cognome(cognome);

    rewind(file_valutazione);
    while (!feof(file_valutazione) && trovato == 0)
    {
        fread(&tmp, sizeof(val_guidatore), 1, file_valutazione);
        cont+=1;

        if (!feof(file_valutazione))
            if(!strcmp(tmp.nome_guidatore,nome )&& !strcmp(tmp.cognome_guidatore,cognome )){
                trovato = 1;


			float tot,media;
			size_t len;
			do
			{
				flag=False;
				printf("\tVALUTAZIONE --> " );
				fgets(guidatore.valuta, 5, stdin);
				rimuovi_accapo(guidatore.valuta);
				len = strlen(guidatore.valuta);
				if(len==0) flag=True;;
				val_int=atoi(guidatore.valuta);
				for(i=0; i<strlen(guidatore.valuta); i++)
				{
					if(isdigit(guidatore.valuta[i])==0)    flag=True;
				}
				if(val_int<1)       flag=True;
				if(val_int>10)     flag=True;
			}while(flag==True);


			printf("\n\nmedia: %f", tmp.media);
			if(tmp.media > 0)
				tot = (tmp.media*tmp.cont_persone)+val_int;
			else
				tot = val_int;
			media = (tot/(tmp.cont_persone + 1));

			tmp.media = media;
			tmp.cont_persone++;

			fseek(file_valutazione,(cont - 1)*sizeof(val_guidatore), SEEK_SET);
			fwrite(&tmp, sizeof(val_guidatore), 1, file_valutazione);
			printf("\nvalutazione inserita");
			printf("\n\nmedia: %f", tmp.media);
			printf("\nvalutazioni totali: %d", tmp.cont_persone);
		  }
    }

    if (!trovato) {
        puts ("\n\nGuidatore non trovato");
    }
}
/**
 * In questa sezione viene calcolato il miglior guidatore, controllando tutte le medie
 * e infine far visualizzare il guidatore con la media piu alta
 */
void miglior_guidatore(FILE *file_valutazione)
{
	float max_media=-1;
	val_guidatore guidatore;

	fseek(file_valutazione, 0, SEEK_SET);
    while (!feof(file_valutazione))
    {
  	  fread(&guidatore, sizeof(val_guidatore), 1, file_valutazione);
  	  if(!feof(file_valutazione))
  		  if(max_media<guidatore.media)
  			  max_media=guidatore.media;
    }

    fseek(file_valutazione, 0, SEEK_SET);
    puts("Guidatori con la media piu' alta:\n");
    printf("%-10s %-10s %-10s %-10s %-10s\n", "Codice", "Nome", "Cognome", "Media", "Valutazioni totali");
    while (!feof(file_valutazione))
      {
    	  fread(&guidatore, sizeof(val_guidatore), 1, file_valutazione);
    	  if(!feof(file_valutazione))
			  if(max_media==guidatore.media)
			  {
					printf("%-10d %-10s %-10s %-10f %-10d\n", guidatore.codice, guidatore.nome_guidatore, guidatore.cognome_guidatore, guidatore.media, guidatore.cont_persone);
			  }
      }
}

