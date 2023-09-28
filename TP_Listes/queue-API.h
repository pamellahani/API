#ifndef QUEUE_API_H
#define QUEUE_API_H

#include "liste-API.h"

struct queue{
    liste_t *l;
};

/* Par défaut, les éléments des listes seront de type void*
 *
 * En définissant le type elem_t avant et en définissant ELEM_T_DEFINED,
 * on peut utiliser un autre type si besoin. Attention alors de bien
 * vérifier que elem_t est connu correctement dans tous les fichiers compilés.
 */
#ifndef ELEM_T_DEFINED
typedef void *elem_t;
#define ELEM_T_DEFINED
#endif

typedef struct queue queue_t;

/* Spécification de queue_init :

But : Initialise la queue donnée en entrée

Entrée(s) : Queue l

Retour : ne retourne rien

Pré-condition : aucune

Complexité : O(1)

*/

void queue_init(queue_t *l);

/* Spécification de queue_alloc :

But : Alloue dynamiquement de la mémoire pour la queue

Entrée(s) : Aucune

Retour : Retourne une queue dont l'objet a été alloué

Pré-condition : Aucune

Complexité : O(1)

*/
queue_t *queue_alloc();

/* Spécification de queue_destroy :

But : Détruit chaque maillon de la queue

Entrée(s) : Queue l

Retour : ne retourne rien

Pré-condition : aucune

Complexité : 

*/

void queue_destroy(queue_t *l);

/* Spécification de queue_free :

But : Détruit chaque maillon de la queue et détruit l'élément de type queue

Entrée(s) : Queue l

Retour : ne retourne rien

Pré-condition : aucune

Complexité : O(n)

*/
void queue_free(queue_t *l);

/* Spécification de queue_insere :

But : Insère un nouvel élément à la queue (à la fin)

Entrée(s) : 

Retour : 

Pré-condition : 

Complexité : 

*/
void queue_insere(queue_t *l, elem_t e);

/* Spécification de queue_tete :

But : Renvoie la valeur de la tête de la queue

Entrée(s) : une queue

Retour : renvoie un pointeur sur la tête de la queue (premier élément inséré)

Pré-condition : queue non vide

Complexité : O(n)

*/

elem_t queue_tete(queue_t *l);

/* Spécification de queue_enleve :

But : Enlève un élément de la queue (le premier qui est entré dans la liste)

Entrée(s) : une queue l

Retour : Retourne l'élément e qui a été défilé (la tête)

Pré-condition : queue non vide

Complexité : O(1)

*/
elem_t queue_enleve(queue_t *l);

/* Spécification de queue_vide :

But : vérifie qu'une queue est vide

Entrée(s) : une queue

Retour : 1 si elle est vide, 0 sinon.

Pré-condition : aucune

Complexité : O(1)

*/
int queue_vide(const queue_t *q); 

#endif
