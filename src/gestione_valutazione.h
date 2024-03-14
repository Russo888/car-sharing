#ifndef GESTIONE_VALUTAZIONE_H_
#define GESTIONE_VALUTAZIONE_H_

void aggiungi_al_file(char nome[100], char cognome[100], FILE *file_valutazione);
void inserimento_valutazione(FILE *file_valutazione);
void miglior_guidatore(FILE *file_valutazione);

#endif /* GESTIONE_VALUTAZIONE_H_ */
