#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void rotate(list_t list, unsigned distance) {
	for (int i = 0; i < distance; i++) {
		list_iterator_t prvi= list_iterator(list);
		list_iterator_t zadnji = list_reverse_iterator(list);
		list_insert(prvi, list_get(zadnji));
		list_remove(zadnji);
	}
}

void main() {
	list_t lista = list_new();
	for (int i = 0; i < 10; i++) {
		list_add(lista, rand() % 10);
	}
	rotate(lista,3);

}