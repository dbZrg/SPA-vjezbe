#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

#define MAX_LINE_SIZE 1024

void print_book(struct book* book) {
	if (book) {
		printf("id: %u, name: %s, author:%s, price:%u\n",
			book->id, book->name, book->author, book->price);
	}
}

int load_books(const char *file_name, struct book **books, unsigned *num_books) {

	FILE *file_stream;
	char line[MAX_LINE_SIZE];
	struct book *pbook;

	/* otvaranje datoteke */
	file_stream = fopen(file_name, "r");
	if (file_stream == NULL) {
		printf("Nije moguce otvoriti datoteku %s!\n", file_name);
		return -1;
	}

	/* brojanje knjiga, tj. redaka u datoteci */
	*num_books = 0;
	while (fgets(line, MAX_LINE_SIZE, file_stream))
		++*num_books;

	/* vracanje kursora na pocetak datoteke */
	if (fseek(file_stream, 0, SEEK_SET))
		return -2;

	/* alociranje memorije */
	if ((*books = malloc(*num_books * sizeof(struct book))) == NULL) {
		printf("Nije moguce alocirati memoriju za %u knjiga!\n", *num_books);
		return -3;
	}

	/* ucitavanje podataka */
	pbook = *books;
	fseek(file_stream, 3, SEEK_SET); // dodano da se izbjegnu prva tri (cudna/nepoznata/misteriozna) znaka u fileu 
	while (fgets(line, MAX_LINE_SIZE, file_stream)) {
		pbook->id = (unsigned)atoi(strtok(line, ";"));
		strcpy(pbook->name, strtok(NULL, ";"));
		strcpy(pbook->author, strtok(NULL, ";"));
		pbook->price = (unsigned)atoi(strtok(NULL, ";"));
		++pbook;
	}

	/* zatvaranje datoteke */
	fclose(file_stream);

	return 0;
}

//////////// MOJE FUNKCIJE ////////////

struct bst_book* bst_new_book() {
	struct bst_book *novi = malloc(sizeof(struct bst_book));
	novi = NULL;
	return novi;
}

void add_bst_book(struct bst_book **root, struct book knj) {
	if (!(*root)) {
		*root = malloc(sizeof(struct bst_book));
		(*root)->knjiga = knj;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}
	if ((*root)->knjiga.id > knj.id)
		add_bst_book(&(*root)->left, knj);
	else if ((*root)->knjiga.id < knj.id)
		add_bst_book(&(*root)->right, knj);
	else
		return;
}

void bst_print_inorder(struct bst_book *root) {
	if (!root) return;
	bst_print_inorder(root->left);
	printf("%s - %u\n", root->knjiga.name, root->knjiga.price);
	bst_print_inorder(root->right);
}

void bst_inorder_file(struct bst_book *root, FILE *fp) {
	if (!root) return;
	bst_inorder_file(root->left, fp);
	fprintf(fp, "%u, %s, %s, %u\n", 
		root->knjiga.id, root->knjiga.name, root->knjiga.author, root->knjiga.price);
	bst_inorder_file(root->right, fp);
}

void bst_postorder_file(struct bst_book *root, FILE *fp) {
	if (!root) return;
	bst_postorder_file(root->left, fp);
	bst_postorder_file(root->right, fp);
	fprintf(fp, "%u, %s, %s, %u\n",
		root->knjiga.id, root->knjiga.name, root->knjiga.author, root->knjiga.price);
}

void bst_preorder_file(struct bst_book *root, FILE *fp) {
	if (!root) return;
	fprintf(fp, "%u, %s, %s, %u\n",
		root->knjiga.id, root->knjiga.name, root->knjiga.author, root->knjiga.price);
	bst_preorder_file(root->left, fp);
	bst_preorder_file(root->right, fp);
}

// ne-rekurzivni pokusaj funkcije za inorder upis u file
//void bst_inorder_file(struct bst_book *root) {
//	FILE *inor = fopen("knjigeInorder.csv", "w");
//	char line[MAX_LINE_SIZE];
//	struct bst_book *trn = root;
//	struct bst_book *zad = root;
//
//	for (;;) {
//		if (trn->left != NULL && trn->left != zad) {
//			trn = trn->left;
//			continue;
//		}
//		if (trn->right != NULL && trn->right != zad) {
//			fprintf(inor, "%u, %s, %s, %u\n",
//				trn->knjiga.id, trn->knjiga.name, trn->knjiga.author, trn->knjiga.price);
//			zad = trn;
//			trn = trn->right;
//			continue;
//		}
//		fprintf(inor, "%u, %s, %s, %u\n",
//			trn->knjiga.id, trn->knjiga.name, trn->knjiga.author, trn->knjiga.price);
//		trn = root;
//	}
//
//	fclose(inor);
//}

void delete_bst_book(struct bst_book *root) {
	if (!root) return;
	delete_bst_book(root->left);
	delete_bst_book(root->right);
	free(root);
}