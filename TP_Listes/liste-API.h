#ifndef LISTE_API_H
#define LISTE_API_H

#include "public.h"

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

/* Initialise une liste vide
 *
 * Entrée : un pointeur sur la liste
 *
 * Effet de bord : la liste est initialisée
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 *
 * Propriété : une liste doit être initialisée avant d'être utilisée
 * par les autres fonctions
 *
 * Remarque : comportement indéfini si la liste était déjà initialisée
 */
void liste_init(liste_t *l);

/* Alloue et initialise une liste vide
 *
 * Retour : pointeur sur une liste initialisée
 * Effet de bord : la liste a été allouée avec malloc puis initialisée
 */
liste_t *liste_alloc();

/* Détruit une liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Effet de bord : la liste est détruite avec son contenu (tous les
 * maillons sont supprimés) et elle ne pourra plus être utilisée dans
 * les autres fonctions tant qu'elle n'est pas réinitialisée
 */
void liste_destroy(liste_t *l);

/* Détruit et libère une liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Effet de bord : comme pour liste_destroy. En outre, la mémoire de
 * la liste est libérée.
 *
 * Pré-condition : la liste a été allouée par liste_alloc()
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
void liste_free(liste_t *l);

/* vérifie si une liste est vide
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : 1 si la liste est vide, 0 sinon
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
int liste_vide(const liste_t *l);

/* ajoute un élément en tête d'une liste
 *
 * Entrées :
 * - un pointeur sur la liste
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement alloué
 * et inséré en tête de liste
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
void liste_insere(liste_t *l, elem_t elem);

/* ajoute un élément en queue d'une liste
 *
 * Entrées :
 * - un pointeur sur la liste
 * - un élément de type elem_t
 *
 * Effet de bord : un maillon contenant `elem` est dynamiquement alloué
 * et inséré en queue de liste
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
void liste_insere_fin(liste_t *l, elem_t elem);

/* récupère l'élément en tête de liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : la valeur du premier maillon de la liste
 *
 * Pré-condition : la liste n'est pas vide
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
elem_t liste_tete(const liste_t *l);

/* récupère l'élément en tête de liste en l'enlevant de la liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : la valeur du premier maillon de la liste
 *
 * Effet de bord : le premier maillon est supprimé
 *
 * Pré-condition : la liste n'est pas vide
 *
 * Pré-condition : le pointeur sur la liste n'est pas NULL
 */
elem_t liste_enleve(liste_t *l);

#ifdef LISTE_AVEC_MAILLON
/* La liste expose la notion de maillon. On peut s'en servir pour
 * traverser la liste
 */
#include "liste-maillon-API.h"
#endif

#ifdef LISTE_AVEC_ITERATEUR
/* La liste expose la notion d'itérateur qu'on peut utiliser pour
 * traverser la liste sans exposer la notion de maillon.
 */
#include "liste-iterateur-API.h"
#endif

#endif
