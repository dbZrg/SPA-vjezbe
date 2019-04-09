/* Implementacija sucelja ATP stoga jednostruko povezanom listom. */

#include <stdlib.h>
#include "stack.h"

struct node {
	stack_element_t value;
	struct node *next;
};

struct stack_tag {
	struct node *head;
	int size;
};

/* O(1) */
stack_t stack_new() {
	stack_t stack = malloc(sizeof(struct stack_tag));
	stack->head = NULL;
	stack->size = 0;
	return stack;
}

/* O(1) */
void stack_delete(stack_t stack) {
	while (stack->head != NULL) {
		struct node *temp = stack->head;
		stack->head = stack->head->next;
		free(temp);
	}
	free(stack);
}

/* O(1) */
void stack_push(stack_t stack, stack_element_t elem) {
	struct node *node = malloc(sizeof(struct node));
	node->value = elem;
	node->next = stack->head;
	stack->head = node;
	++stack->size;
}

/* O(1) */
stack_element_t stack_pop(stack_t stack) {
	struct node *node;
	stack_element_t value;
	node = stack->head;
	value = node->value;
	stack->head = node->next;
	free(node);
	--stack->size;
	return value;
}

/* O(1) */
stack_element_t stack_top(stack_t stack) {
	return stack->head->value;
}

/* O(1) */
int stack_is_empty(stack_t stack) {
	return stack->head == NULL;
}

/* O(1) */
int stack_size(stack_t stack) {
	return stack->size;
}
