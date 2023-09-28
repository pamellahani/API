#include "liste-maillon-API.h"
#include"liste-API.h"
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
    // Initialisation du tableau
    init_tab();

    // Test avec la fonction maillon_enleve_apres
    liste_t *l = liste_alloc();
    assert(l);

    assert(liste_vide(l));

    liste_insere(l, &tab[0]);
    struct maillon *m = maillon_premier(l); 

    assert(!liste_vide(l));
    
    assert(maillon_element(m) == &tab[0]);

    for(int i=1; i<N; i++) {
        maillon_insere_apres(m,&tab[i]); 
        m = maillon_suivant(m); 
    }

    assert(maillon_element(maillon_dernier(l))==&tab[N-1]);
    m = maillon_dernier(l);

    for(int i = N-1; i <= 0; i--) {
        assert(maillon_enleve_apres(m) == &tab[i]);
        m = maillon_precedent(m);
    }

    // Test avec la fonction maillon_enleve
    liste_t *l2 = liste_alloc();
    assert(l2);

    assert(liste_vide(l2));

    liste_insere(l2, &tab[0]);
    struct maillon *m2 = maillon_premier(l2); 

    assert(!liste_vide(l2));
    
    assert(maillon_element(m2) == &tab[0]);

    for(int i=1; i<N; i++) {
        maillon_insere_apres(m2,&tab[i]); 
        m2 = maillon_suivant(m2); 
    }

    assert(maillon_element(maillon_dernier(l2))==&tab[N-1]);
    m2 = maillon_dernier(l2);

    for(int i = N-1; i <= 0; i--) {
        assert(maillon_enleve(m2) == &tab[i]);
        m2 = maillon_precedent(m2);
    }
    
    // On libère les objets pour lesquels de la mémoire a été allouée et qui ne sera plus utilisée.
    liste_free(l);
    liste_free(l2);
    printf("Test OK (no failed assertions)\n");
    
    return 0;
}