#include <stdlib.h>
#include "queue-API.h"
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
	// On crée un tableau de 100 éléments contenant en ordre croissant [100,..,.199].
	init_tab(); 
	// On alloue de la mémoire pour une queue
	queue_t *q = queue_alloc(); 
	assert(q); 

	queue_init(q);
	// On s'assure que l'allocation a été faite correctement, en s'assurant que la queue est bien vide
	assert(queue_vide(q)); 

	// On insère le premier élémenmt du tableau (tab[0] = 100) dans la queue
	queue_insere(q,&tab[0]);

	
	// On s'assure que la queue n'est plus vide désormais
	assert(!queue_vide(q)); 

	
	// On insère le reste des éléments du tableau dans la queue
	for(int i=1; i<N; i++) {
		queue_insere(q, &tab[i]);
	}
	
	// On enlève chaque élément de la queue
	for(int i=0; i<N; i++) {
		assert(queue_enleve(q) == &tab[i]);
	}

	// On supprime q

	queue_free(q);

	printf("Test OK (no failed assertions)\n");

	return 0; 

}
