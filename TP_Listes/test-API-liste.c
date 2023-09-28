#include "liste-API.h"
#include <assert.h>
#include <stdio.h>

#define N 100

int tab[N];

void init_tab() {
	for(int i=0; i<N; i++) {
		tab[i]=100+i;
	}
}

int main() {
	init_tab();
	
	liste_t *l = liste_alloc();
	assert(l);

	assert(liste_vide(l));

	liste_insere(l, &tab[0]);
	assert(!liste_vide(l));

	assert(liste_tete(l) == &tab[0]);

	for(int i=1; i<N; i++) {
		liste_insere(l, &tab[i]);
	}
	
	for(int i=N-1; i>=0; i--) {
		assert(liste_enleve(l) == &tab[i]);
	}
	
	liste_free(l);

	printf("Test OK (no failed assertions)\n");
	
	return 0;
}
