#ifndef _AVL_TREE_H
#define _AVL_TREE_H

struct node {
  int data;
  int height;
  struct node *left;
  struct node *right;
};

struct node *avl_find(struct node *root, int x);
struct node *avl_insert(struct node *root, int x);
void node *avl_erase(struct node *root, int x);

#endif
