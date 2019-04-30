#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "trie.h"

int main() {

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

	/* knjige su u trieu, ne trebaju nam vise kao zaseban niz */
	//free(books);

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
