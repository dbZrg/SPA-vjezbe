#include <stdio.h>
#include "stack.h"

int* unija(stack_t a, stack_t b) {
	stack_t novi_stog = stack_new();
	static int lista[8];
	int i = 0;
	while (!stack_is_empty(a) || !stack_is_empty(b)) {
		
		if (stack_is_empty(a)) {
			lista[i] = stack_pop(b);
			i++;
		}
		else if (stack_is_empty(b)) {
			lista[i] = stack_pop(a);
			i++;
		}
		else {
			if (stack_top(a) >= stack_top(b)) {
				lista[i] = stack_pop(a);
			}
			else {
				lista[i] = stack_pop(b);
			}
			i++;
		}
	}
	return lista;
}

void main() {
	stack_t stogic_1 = stack_new();
	stack_t stogic_2 = stack_new();
	int *lista;

	stack_push(stogic_1, 1);
	stack_push(stogic_1, 3);
	stack_push(stogic_1, 7);
	stack_push(stogic_1, 8);

	stack_push(stogic_2, 2);
	stack_push(stogic_2, 4);
	stack_push(stogic_2, 6);
	stack_push(stogic_2, 8);

	lista = unija(stogic_1, stogic_2);

	for (int i = 0; i < 8; i++) {
		printf("%d", *(lista+i));
	}
	getchar();
	getchar();
}
