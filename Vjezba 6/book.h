#ifndef BOOK_H_INCLUDED

#define BOOK_H_INCLUDED

#define BOOK_NAME_MAX_LEN 80
#define BOOK_AUTHOR_MAX_LEN	80

struct book {
	unsigned id;
	char name[BOOK_NAME_MAX_LEN + 1];
	char author[BOOK_AUTHOR_MAX_LEN + 1];
	unsigned price;
};

struct bst_book {
	struct book knjiga;
	struct bst_book *left;
	struct bst_book *right;
};

/* ispis knjige */
void print_book(struct book* _book);

/* ucitavanje knjiga iz datoteke */
int load_books(const char *file_name, struct book **books, unsigned *num_books);

//////////// MOJE FUNKCIJE ////////////

/* stvara i vraca novo bst stablo */
struct bst_book* bst_new_book();

/* slaze knjige u BST po id-u */
void add_bst_book(struct bst_book **root, struct book knj);

/* inorder ispis knjiga iz BST-a */
void bst_print_inorder(struct bst_book *root);

/* inorder ispis knjiga iz BST-a u file */
void bst_inorder_file(struct bst_book *root, FILE *fp);

/* postorder ispis knjiga iz BST-a u file */
void bst_postorder_file(struct bst_book *root, FILE *fp);

/* preorder ispis knjiga iz BST-a u file */
void bst_preorder_file(struct bst_book *root, FILE *fp);

/* brise bst_book */
void delete_bst_book(struct bst_book *root);

#endif /* BOOK_H_INCLUDED */
