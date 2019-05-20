/* Implementacija sucelja ATP mape binarnim stablom pretrazivanja. */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

struct node {
	map_element_t elem;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct map_tag {
	struct node *root;
	int size;
	int (*compare)(const map_key_t, const map_key_t);
};

struct map_iterator_tag {
	map_t map;
	struct node *current;
};

static int compare_simple(const map_key_t key1, const map_key_t key2);

static void bst_free(struct node *root);
static struct node **bst_find(struct node **root, map_key_t key, int (*compare)(const map_key_t, const map_key_t));
static int bst_add(struct node **root, map_element_t elem, int (*compare)(const map_key_t, const map_key_t));
static void bst_remove(struct node **root, map_key_t key, int (*compare)(const map_key_t, const map_key_t));
static void bst_remove_node(struct node **node);
static struct node *bst_inorder_successor(struct node *node);
static struct node *bst_min(struct node *node);
static int tree_height(struct node *root);

/* public: ATP interface */

map_t map_new() {
	return map_new_advanced(compare_simple, NULL);
}

map_t map_new_advanced(int (*compare)(const map_key_t, const map_key_t), size_t (*hash)(const map_key_t)) {
	map_t map = malloc(sizeof(struct map_tag));
	map->root = NULL;
	map->size = 0;
	map->compare = compare;
	return map;
}

void map_delete(map_t map) {
	bst_free(map->root);
	free(map);
}

int map_is_empty(map_t map) {
	return map->size == 0;
}

int map_size(map_t map) {
	return map->size;
}

map_value_t map_get(map_t map, map_key_t key) {
	return (*bst_find(&map->root, key, map->compare))->elem.value;
}

void map_put(map_t map, map_key_t key, map_value_t value) {
	map_element_t e;
	e.key = key;
	e.value = value;
	map_put_element(map, e);
}

void map_put_element(map_t map, map_element_t elem) {
	map->size += bst_add(&map->root, elem, map->compare);
}

void map_remove(map_t map, map_key_t key) {
	bst_remove(&map->root, key, map->compare);
	map->size--;
}

int map_has_key(map_t map, map_key_t key) {
	return bst_find(&map->root, key, map->compare) != NULL;
}

map_iterator_t map_iterator(map_t map) {
	map_iterator_t iter = malloc(sizeof(struct map_iterator_tag));
	iter->map = map;
	iter->current = map->root != NULL ? bst_min(map->root) : NULL;
	return iter;
}

map_element_t map_iget(map_iterator_t iter) {
	return iter->current->elem;
}

void map_iput(map_iterator_t iter, map_value_t value) {
	iter->current->elem.value = value;
}

void map_iremove(map_iterator_t iter) {
	int update_root = iter->map->root == iter->current;
	bst_remove_node(&iter->current);
	if (update_root)
		iter->map->root = iter->current;
	iter->map->size--;
}

void map_iterator_next(map_iterator_t iter) {
	iter->current = bst_inorder_successor(iter->current);
}

void map_iterator_set(map_iterator_t iter1, map_iterator_t iter2) {
	iter1->current = iter2->current;
}

int map_iterator_is_valid(map_iterator_t iter) {
	return iter->current != NULL;
}

int map_iterator_is_equal(map_iterator_t iter1, map_iterator_t iter2) {
	return iter1->current == iter2->current;
}

void map_iterator_delete(map_iterator_t iter) {
	free(iter);
}

void map_debug_print_stats(map_t map) {
	printf("TREE MAP STATS\n");
	printf("--------------\n");
	printf("Size: %d\n", map_size(map));
	printf("Tree height: %d\n", tree_height(map->root));
}

/* private: internals */

static int compare_simple(const map_key_t key1, const map_key_t key2) {
	if (key1 > key2)
		return 1;
	else if (key1 < key2)
		return -1;
	else
		return 0;
}

static void bst_free(struct node *root) {

	if (root == NULL)
		return;

	bst_free(root->left);
	bst_free(root->right);
	free(root);

}

static struct node **bst_find(struct node **root, map_key_t key, int (*compare)(const map_key_t, const map_key_t)) {

	while (*root != NULL)
		if (compare((*root)->elem.key, key) > 0)
			root = &(*root)->left;
		else if (compare((*root)->elem.key, key) < 0)
			root = &(*root)->right;
		else
			return root;

	return NULL;

}

/* returns 1 if new element was allocated, 0 is existing was modified */
static int bst_add(struct node **root, map_element_t elem, int (*compare)(const map_key_t, const map_key_t)) {

	struct node *parent = NULL;

	while (*root != NULL)
		if (compare((*root)->elem.key, elem.key) > 0) {
			parent = *root;
			root = &(*root)->left;
		} else if (compare((*root)->elem.key, elem.key) < 0) {
			parent = *root;
			root = &(*root)->right;
		} else {
			(*root)->elem.value = elem.value;
			return 0;
		}

	*root = malloc(sizeof(struct node));
	(*root)->elem = elem;
	(*root)->parent = parent;
	(*root)->left = NULL;
	(*root)->right = NULL;

	return 1;

}

static void bst_remove(struct node **root, map_key_t key, int (*compare)(const map_key_t, const map_key_t)) {
	if (compare((*root)->elem.key, key) == 0) {
		bst_remove_node(root);
	} else {
		struct node **node = bst_find(root, key, compare);
		bst_remove_node(node);
	}
}

static void bst_remove_node(struct node **node) {

	if ((*node)->left == NULL) {

		struct node *old_node = *node;

		*node = (*node)->right;
		if (*node != NULL)
			(*node)->parent = old_node->parent;

		free(old_node);

	} else if ((*node)->right == NULL) {

		struct node *old_node = *node;

		*node = (*node)->left;
		if (*node != NULL)
			(*node)->parent = old_node->parent;

		free(old_node);

	} else {

		/* delete node with two children */
		map_element_t temp;

		/* find inorder predecessor */
		struct node **pred = &(*node)->left;
		while ((*pred)->right != NULL)
			pred = &(*pred)->right;

		/* swap values */
		temp = (*pred)->elem;
		(*pred)->elem = (*node)->elem;
		(*node)->elem = temp;

		bst_remove_node(pred);

	}

}

static struct node *bst_inorder_successor(struct node *node) {
	if(node->right != NULL) {
		return bst_min(node->right);
	} else {
		struct node *parent = node->parent;
		while(parent != NULL && node == parent->right) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

static struct node *bst_min(struct node *node) {
	struct node *current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

static int tree_height(struct node *root) {

	int height_l, height_r;

	if (root == NULL)
		return 0;

	height_l = tree_height(root->left);		/* racunaj visinu lijevog podstabla */
	height_r = tree_height(root->right);	/* racunaj visinu desnog podstabla */

	/* visina trenutnog (pod)stabla je veca od visine lijevog odnosno desnog podstabla
	 * uvecano za 1 tj. visinu trenutnog cvora */
	return 1 + (height_l > height_r ? height_l : height_r);

}
