#ifndef LISTE_MAILLON_API_H
#define LISTE_MAILLON_API_H

#include "liste-API.h"

/* récupère l'élément d'un maillon
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : la valeur du maillon
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
elem_t maillon_element(const struct maillon *m);

/* récupère le premier maillon de la liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : un pointeur sur le premier maillon de la liste ou NULL si
 * la liste est vide
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
struct maillon* maillon_premier(const liste_t *l);

/* récupère le dernier maillon de la liste
 *
 * Entrée : un pointeur sur la liste
 *
 * Retour : un pointeur sur le dernier maillon de la liste ou NULL si
 * la liste est vide
 */
struct maillon* maillon_dernier(const liste_t *l);

/* récupère le maillon suivant dans la liste
 *
 * Entrée : un pointeur sur un maillon
 *
 * Retour : un pointeur sur le maillon suivant de la liste ou NULL si
 * on est en fin de liste
 *
 * Pré-condition : le pointeur sur le maillon n'est pas NULL
 */
struct maillon* maillon_suivant(const struct maillon *m);

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
void maillon_insere_apres(struct maillon *m, elem_t e);

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
elem_t maillon_enleve_apres(struct maillon *m);

#ifndef LISTE_SANS_RETOUR
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
struct maillon* maillon_precedent(const struct maillon *m);

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
void maillon_insere_avant(struct maillon *m, elem_t e);

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
elem_t maillon_enleve(struct maillon *m);

#endif /* LISTE_SANS_RETOUR */

#endif
