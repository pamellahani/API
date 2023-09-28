#include "queue-API.h"
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>


int queue_vide(const queue_t *q){
	assert(q);
	return q->l->tete==NULL; 
}


void queue_init(queue_t *l){
    assert(l);
    l->l->tete = NULL;
}


queue_t *queue_alloc(){
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    q->l = liste_alloc();
    return q;
}

void queue_destroy(queue_t *q){
    assert(q);
    liste_free(q->l);
}

void queue_free(queue_t *l){
    queue_destroy(l);
    free(l);
}


void queue_insere(queue_t *q, elem_t e){
    assert(q); 
    liste_insere_fin(q->l,e); 
}


elem_t queue_tete(queue_t *q){
    assert(q); 
    assert (!queue_vide(q)); 
    return liste_tete(q->l) ; 
}


elem_t queue_enleve(queue_t *q){
    return liste_enleve(q->l); 
}