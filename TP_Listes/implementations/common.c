/* Code commun à toutes les implémentations de liste
 *
 * Note : si besoin, chacune de ces fonctions peuvent ne pas être générées
 * en définissant le symbole de préprocesseur correspondant dans public.h
 */


#include "liste-API.h"
#include <stdlib.h>

#ifndef COMMON_LISTE_ALLOC
liste_t *liste_alloc() {
	liste_t *l = malloc(sizeof(*l));
	liste_init(l);
	return l;
}
#endif

#ifndef COMMON_LISTE_FREE
void liste_free(liste_t *l) {
	liste_destroy(l);
	free(l);
}
#endif
