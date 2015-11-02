#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE


struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct node *bst_find(struct node *root, int x);
struct node * bst_insert(struct node *root, int x);
void bst_erase(struct node *root, int x);

void bst_inorder(struct node *root);
void bst_preorder(struct node *root);
#endif
