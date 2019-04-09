#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack_element_t stack_multipop(stack_t s, int n) {
	stack_element_t zadnji;
	for (int i = 0; i < n; i++) {
		zadnji = stack_pop(s);
		if (stack_is_empty(s)) {
			break;
		}
	}
	return zadnji;
}


void main() {
	stack_t stogic = stack_new();
	
	for (int i = 0; i < 10; i++) {
		stack_push(stogic, rand() % 10);
	}
	stack_multipop(stogic, 3);

}