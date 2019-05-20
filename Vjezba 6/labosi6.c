#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "book.h"
#include "map.h"
#include "djb2.h"
#include "list.h"

void ukupan_broj_autora(struct book *knjige, unsigned broj) {
	

	map_t mapa;
	mapa = map_new_advanced(strcmp, djb2);

	for (int i = 0; i < broj; i++) {

		if (map_has_key(mapa,knjige[i].author)) {
			continue;
		}
		else {
			map_put(mapa, knjige[i].author, 1);
		}
		
	}
	printf("broj knjiga: %d , broj autora: %d \n", broj, map_size(mapa));

	map_delete(mapa);
}


void autori_i_knjige(struct book *knjige, unsigned broj) {

	map_t mapa;
	mapa = map_new_advanced(strcmp, djb2);

	for (int i = 0; i < broj; i++) {
		if (map_has_key(mapa, _strdup(knjige[i].author))) {
			map_put(mapa, knjige[i].author, map_get(mapa, knjige[i].author)+1);
		}
		else {
			map_put(mapa, knjige[i].author, 1);
		}
	}

	map_iterator_t iter;

	for (iter = map_iterator(mapa); map_iterator_is_valid(iter); map_iterator_next(iter)) {
	printf(" %s - %d \n", map_iget(iter).key, map_iget(iter).value);
	}
	
	map_delete(mapa);
}

/*
void autori_i_knjige_popis(struct book *knjige, unsigned broj) {
	
}
*/

int main() {

	struct book *knjige_niz = NULL;
	unsigned broj_knjiga = 0;

	if (load_books("knjige.csv", &knjige_niz, &broj_knjiga))
		return -1;

	ukupan_broj_autora(knjige_niz, broj_knjiga);

	autori_i_knjige(knjige_niz, broj_knjiga);

	//autori_i_knjige_popis (knjige_niz, broj_knjiga);

	free(knjige_niz);

	return 0;

}



