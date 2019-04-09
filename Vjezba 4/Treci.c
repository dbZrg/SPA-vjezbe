#include <stdio.h>
#include "list.h"
#include "stack.h"

list_t unija(stack_t a, stack_t b) {
	stack_t novi_stog = stack_new();
	list_t lista = list_new();

	while (!stack_is_empty(a) || !stack_is_empty(b)) {
		
		if (stack_is_empty(a)) {
			list_add (lista ,stack_pop(b));
			
		}
		else if (stack_is_empty(b)) {
			list_add(lista, stack_pop(a));
	
		}
		else {
			if (stack_top(a) >= stack_top(b)) {
				list_add(lista, stack_pop(a));
			}
			else {
				list_add(lista, stack_pop(b));
			}
	
		}
	}
	return lista;
}

void main() {
	stack_t stogic_1 = stack_new();
	stack_t stogic_2 = stack_new();
	list_t lista;

	stack_push(stogic_1, 1);
	stack_push(stogic_1, 3);
	stack_push(stogic_1, 7);
	stack_push(stogic_1, 8);

	stack_push(stogic_2, 2);
	stack_push(stogic_2, 4);
	stack_push(stogic_2, 6);
	stack_push(stogic_2, 8);

	lista = unija(stogic_1, stogic_2);

	list_iterator_t itter = list_iterator(lista);
	while (list_iterator_is_valid(itter)) {
		printf("%d", list_get(itter));
		list_iterator_next(itter);
	}

	getchar();
	getchar();
}
