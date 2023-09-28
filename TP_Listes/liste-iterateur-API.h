#ifndef LISTE_ITERATEUR_API_H
#define LISTE_ITERATEUR_API_H

#include "liste-API.h"

/* Les différents types d'itérateur pouvant être demandés */
enum iterateur_type {
	avant,
	arriere,
	bidir_avant,
	bidir_arrier,
};

/* récupère un itérateur du type demandé
 *
 * Entrées :
 * - un pointeur sur une liste
 * - le type d'itérateur souhaité
 *
 * Retour : un pointeur sur un itérateur alloué ou NULL si le type
 * demandé n'est pas disponible
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
iterateur_t* iterateur_alloue(const liste_t *l,
			      enum iterateur_type type);

/* détruit un itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Effet de bord : l'itérateur est détruit, sa mémoire est libérée
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 */
void iterateur_libere(const liste_t *l);

/* fin de l'itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Retour : 1 si l'itérateur a encore des éléments à énumérer, 0 sinon
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 *
 * Attention : pour un iterateur arriere, l'élément suivant de
 * l'itérateur est l'élément précédent dans la liste
 */
int iterateur_a_suivant(iterateur_t *it);

/* récupère l'élément suivant avec un itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Retour : l'élément suivant
 *
 * Pré-condition : l'itérateur a un élément suivant
 *   (iterateur_a_suivant(it) == 1)
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 *
 * Attention : pour un iterateur arriere, l'élément suivant de
 * l'itérateur est l'élément précédent dans la liste
 */
elem_t iterateur_suivant(iterateur_t *it);

/* début de l'itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Retour : 1 si l'itérateur a encore des éléments à énumérer en
 * arrière, 0 sinon
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 *
 * Pré-condition : l'itérateur est bi-directionnel
 *
 * Attention : pour un iterateur arriere, l'élément précédent de
 * l'itérateur est l'élément suivant dans la liste
 */
int iterateur_a_precedent(iterateur_t *it);

/* récupère l'élément précédent avec un itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Retour : l'élément précédent
 *
 * Pré-condition : l'itérateur a un élément précédent
 *   (iterateur_a_precedent(it) == 1)
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 *
 * Pré-condition : l'itérateur est bi-directionnel
 *
 * Attention : pour un iterateur arriere, l'élément précédent de
 * l'itérateur est l'élément suivant dans la liste
 */
elem_t iterateur_precedent(iterateur_t *it);

/* ajoute un élément après le dernier élément récupéré avec l'itérateur
 *
 * Entrées :
 * - un pointeur sur un itérateur
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement
 * alloué et inséré après le maillon contenant le dernier élément
 * récupéré avec l'itérateur. Si aucun élément n'a encore été
 * récupéré, l'élément est inséré en tête de liste.
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 */
void iterateur_insere_apres((iterateur_t *it, elem_t e);

/* ajoute un élément avant le dernier élément récupéré avec l'itérateur
 *
 * Entrées :
 * - un pointeur sur un itérateur
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement
 * alloué et inséré avant le maillon contenant le dernier élément
 * récupéré avec l'itérateur. Si aucun élément n'a encore été
 * récupéré, l'élément est inséré en tête de liste.
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 */
void iterateur_insere_avant((iterateur_t *it, elem_t e);

/* enlève le dernier élément récupéré avec l'itérateur
 *
 * Entrée : un pointeur sur un itérateur
 *
 * Retour : la valeur de l'élémént enlevé
 *
 * Effet de bord : le maillon de l'élément est supprimé
 *
 * Pré-condition : le pointeur sur l'itérateur n'est pas NULL
 *
 * Pré-condition : un élément a été récupéré avec l'itérateur et il
 * n'a pas été supprimé
 */
elem_t iterateur_enleve(iterateur_t *it);


#endif
