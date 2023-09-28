
#include "liste-API.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

// Type LISTE

/* type interne, non défini dans public.h car non exposé par l'API */
struct maillon {
	struct maillon* suivant;
	struct maillon* prec;
	elem_t e;
};

// complexité de O(1)
void liste_init(liste_t *l) {
	assert(l);

	l->tete = NULL;
}

// Complexité O(n)
void liste_destroy(liste_t *l) {
	assert(l);

	while (!liste_vide(l)) {
		liste_enleve(l);
	}
	/* pour espérer une segfault si on réutilise la liste sans
	 * l'initialiser */
	l->tete = (struct maillon*)(-1);
}

// Complexité O(1)
int liste_vide(const liste_t *l) {
	assert(l);

	return l->tete == NULL;
}

// Complexité O(1)
void liste_insere(liste_t *l, elem_t elem) {
	assert(l);

	struct maillon *m = malloc(sizeof(struct maillon));
	m->e = elem;
	m->suivant = l->tete;
	l->tete = m;
}

// Complexité O(n)
void liste_insere_fin(liste_t *l, elem_t elem) {
	assert(l);

	struct maillon *m = malloc(sizeof(struct maillon));
	m->e = elem;
	m->suivant = NULL;

	struct maillon **prev_p = &l->tete;
	while (*prev_p != NULL) {
		prev_p = &((*prev_p)->suivant);
	}
	*prev_p = m;
};

// Complexité O(1)
elem_t liste_tete(const liste_t *l) {
	assert(l);
	assert(!liste_vide(l));
	
	return l->tete->e;
}


// Complexité O(1)	
elem_t liste_enleve(liste_t *l) {
	elem_t e = liste_tete(l);
	struct maillon *m = l->tete;
	l->tete = m->suivant;
	free(m);
	return e;
}

// TYPE MAILLON

/* récupère l'élément d'un maillon
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : la valeur du maillon
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
// O(1)
elem_t maillon_element(const struct maillon *m){
	assert(m!=NULL);
	return m->e;
}

/* récupère le premier maillon de la liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : un pointeur sur le premier maillon de la liste ou NULL si
 * la liste est vide
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
// O(1)
struct maillon* maillon_premier(const liste_t *l){
	return l->tete;
}

/* récupère le dernier maillon de la liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : un pointeur sur le dernier maillon de la liste ou NULL si
 * la liste est vide
 */
// O(n), n étant la taille de la liste;
struct maillon* maillon_dernier(const liste_t *l){
	struct maillon* m = l->tete;
	if (m == NULL){
		return m;
	}
	while(m->suivant != NULL){
		m = m->suivant;
	}
	return m;

}

/* récupère le maillon suivant dans la liste
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : un pointeur sur le maillon suivant de la liste ou NULL si
 * on est en fin de liste
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */

// O(1)
struct maillon* maillon_suivant(const struct maillon *m){
	if (m == NULL){
		return NULL;
	}
	return m->suivant;
}

/* ajoute un élément après un maillon
 *
 * Entrées :
 * - un pointeur sur un maillon
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement alloué
 * et inséré après le maillon
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
// O(1)
void maillon_insere_apres(struct maillon *m, elem_t e){
	struct maillon *m1 = malloc(sizeof(struct maillon));
	m1->e = e;
	m1->suivant = NULL;
	m->suivant = m1;
	m1->prec = m;
}

/* enlève un élément après un maillon
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : la valeur du maillon suivant
 *
 * Effet de bord : le maillon suivant est supprimé
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 *
 * Pré-condition : le maillon n'est pas le dernier de la liste
 */
// O(1)
elem_t maillon_enleve_apres(struct maillon *m){
	if (m == NULL || m->suivant == NULL){
		return NULL;
	}
	elem_t res = m->suivant->e;
	m->suivant = m->suivant->suivant;
	m->suivant->suivant->prec = m->prec;
	m = m->suivant;
	return res;
}

/* Les fonctions suivantes ne seront ầ fournir que lorsque le modèle
 * de liste implémenté le permet (listes doublement chaînées par exemple)
 * 
 * Si ce n'est pas le cas, le fichier d'entête de l'implémentation doit
 * définit LISTE_SANS_RETOUR pour éviter d'avoir ces déclarations.
 */

/* récupère le maillon precedent dans la liste
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : un pointeur sur le maillon precedent de la liste ou NULL si
 * on est en début de liste
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
// O(1)
struct maillon* maillon_precedent(const struct maillon *m){
	return m->prec;
}

/* ajoute un élément après un maillon
 *
 * Entrées :
 * - un pointeur sur un maillon
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement alloué
 * et inséré avant le maillon
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
// O(1)
void maillon_insere_avant(struct maillon *m, elem_t e){
	struct maillon *av = malloc(sizeof(struct maillon));
	av->e = e;
	//m->prec = av;
	av->prec = m->prec;
	m->prec->suivant = av;
	av->suivant = m;
	
}

/* enlève un élément dans un maillon
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : la valeur du maillon
 *
 * Effet de bord : le maillon est supprimé
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */

// O(1)
elem_t maillon_enleve(struct maillon *m){
	if (m == NULL){
		return NULL;
	}
	elem_t el = m->e;
	m->prec->suivant = m->suivant;
	m->suivant->prec = m->prec;
	m = m->suivant;
	return el;

	/* struct maillon *tmp = m;
	m = m->suivant;
	m */

}
