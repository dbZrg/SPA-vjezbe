#ifndef STACK_H_INCLUDED

#define STACK_H_INCLUDED

typedef int stack_element_t;
typedef struct stack_tag *stack_t;

stack_t stack_new();									/* stvara novi (prazni) stog */
void stack_delete(stack_t stack);						/* unistava stog */
void stack_push(stack_t stack, stack_element_t elem);	/* ubacuje element na vrh stoga */
stack_element_t stack_pop(stack_t stack);				/* uklanja element sa vrha stoga */
stack_element_t stack_top(stack_t stack);				/* vraca element sa vrha stoga */
int stack_is_empty(stack_t stack);						/* vraca 1 ako je stog prazan, a 0 inace */
int stack_size(stack_t stack);							/* vraca broj elemenata u stogu */

#endif /* STACK_H_INCLUDED */
