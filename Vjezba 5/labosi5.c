#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "trie.h"


struct node {
	int value;
	char ime[100];
	int cijena;
	struct node *left;
	struct node *right;
};

struct node *bst_add_iterative(struct node **root, int value, char *ime, int cijena) {

	while (*root != NULL)
		if ((*root)->value > value)
			root = &(*root)->left;
		else if ((*root)->value < value)
			root = &(*root)->right;
		else
			/* duplikat: (*root)->value == value */
			return *root;

	*root = malloc(sizeof(struct node));
	(*root)->value = value;
	strcpy((*root)->ime, ime);
	(*root)->cijena = cijena;
	(*root)->left = NULL;
	(*root)->right = NULL;

	return *root;

}

/* ispisuje sve cvorove stabla u inorder poretku */
void tree_print_inorder(struct node *root) {

	if (root == NULL)
		return;

	tree_print_inorder(root->left);		/* inorder poretkom ispisi lijevo podstablo */
	printf("%d - %s - %d \n ", root->value,root->ime,root->cijena);			/* ispisi trenutni cvor */
	tree_print_inorder(root->right);	/* inorder poretkom ispisi desno podstablo */

}

int main() {

	struct node *bst = NULL;
	trie_t root;
	struct book *books;
	unsigned num_books;
	char book_name[BOOK_NAME_MAX_LEN + 1];
	unsigned i;

	/* ucitavanje knjiga iz datoteke */
	if (load_books("knjige.csv", &books, &num_books))
		return -1;

	/* korijen triea, pocetak svih rijeci, uvijek alociran */
	root = trie_new_node();

	/* ubacivanje knjiga u trie */
	for (i = 0; i < num_books; i++)
		trie_insert_word(root, books[i].name);


	// 2. ZADATAK  ---- pocetak
	for (i = 0; i < num_books; i++)
		bst_add_iterative(&bst, books[i].id, books[i].name, books[i].price);

	tree_print_inorder(bst);
	// 2. ZADATAK  ---- kraj

	/* knjige su u trieu, ne trebaju nam vise kao zaseban niz */
	free(books);

	/* pretrazivanje knjiga */
	while (1) {
		int search_result = 0;

		printf("\nUpisi ime knjige (prazan string za izlaz iz programa): ");
		gets(book_name);

		if (!strcmp(book_name, ""))
			break;

		search_result = trie_search_word(root, book_name);
		printf("'%s' %s ispravan naziv knjige.\n", book_name, search_result ? "je" : "nije");
		if (!search_result) {
			printf("Moguci kandidati su:\n");
			trie_print_prefixed_word(root, book_name);
		}
	}

	return 0;
}
