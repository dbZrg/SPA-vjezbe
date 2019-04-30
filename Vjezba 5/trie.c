#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define NUM_ASCII_CHARS	256

struct trie_node {
    int terminal;
    trie_t children[NUM_ASCII_CHARS];
};

trie_t trie_new_node() {

    trie_t node = malloc(sizeof(struct trie_node));

    if (node) {
        int i;
        node->terminal = 0;
        for(i = 0; i < NUM_ASCII_CHARS; i++)
            node->children[i] = NULL;
    }

    return node;

}

void trie_delete_node(trie_t node) {

    int i;

    if (node == NULL)
        return;

    for (i = 0; i < NUM_ASCII_CHARS; i++)
        trie_delete_node(node->children[i]);

    free(node);

}
// 1. ZADATAK  ---- pocetak
void trie_insert_word(trie_t root, char *word) {

	int asci_slovo;


	for (int i = 0; i < strlen(word); i++) {
		asci_slovo = (int)word[i];
		if (asci_slovo < 0) {
			continue;
		}
		if (!root->children[asci_slovo]) {
			root->children[asci_slovo] = trie_new_node();
		}
		root = root->children[asci_slovo];
	}
	root->terminal = 1;
}

int trie_search_word(trie_t root, char *word) {
	
	int asci_slovo;

	for (int i = 0; i < strlen(word); i++) {
		asci_slovo = (int)word[i];

		if (!root->children[asci_slovo]) {
			return 0;
		}
		root = root->children[asci_slovo];
	}
	if (root->terminal) return 1;
	return 0;
}
// 1. ZADATAK  ---- kraj

void trie_print_node(trie_t node, char* prefix) {

    int ascii_index = 0;

    if (node->terminal)
        printf("%s\n", prefix);

    for (ascii_index = 0; ascii_index < NUM_ASCII_CHARS; ++ascii_index) {
        if (node->children[ascii_index]) {
            size_t len = strlen(prefix);
            char * word = malloc(len + 2);
            strncpy(word, prefix, len);
            word[len] = ascii_index;
            word[len + 1] = '\0';
            trie_print_node(node->children[ascii_index], word);
            free(word);
        }
    }
}

void trie_print_prefixed_word(trie_t root, char *prefix) {

    int i;
    for (i = 0; i < strlen(prefix); ++i){
        char ascii_index = prefix[i];
        if (!root->children[ascii_index]) {
            printf("Nema mogucih kandidata.\n");
            return;
        }

        root = root->children[ascii_index];
    }

    trie_print_node(root, prefix);
}
