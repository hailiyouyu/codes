#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

static struct node *bst_find_min(struct node *);

struct node *bst_find(struct node *root, int x) {
  while (root && root->data != x) {
    if (x < root->data)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

struct node *bst_find_recursively(struct node *root, int x) {
  if (!root || root->data == x)
    return root;
  if (x < root->data)
    return bst_find_recursively(root->left, x);
  else
    return bst_find_recursively(root->right, x);
}

struct node *bst_insert(struct node *root, int x) {
  struct node *parent = 0, *p = root;
  int left = 0;
  while (p && p->data != x) {
    parent = p;
    if (x < p->data) {
      p = p->left;
      left = 1;
    }
    else {
      p = p->right;
      left = 0;
    }
  }
  if (p) {
    puts("elment exists!!!");
  } else {
    p = (struct node *)malloc(sizeof(struct node));
    p->data = x;
    p->left = p->right = 0;

    if (!parent) {
      return p;
    }
    if (left)
      parent->left = p;
    else
      parent->right = p;
  }
  return root;
}

struct node *bst_insert_recursively(struct node *root, int x) {
  if (!root) {
    root = (struct node *)malloc(sizeof(struct node));
    root->data = x;
    root->left = root->right = 0;
  } else if (x < root->data) {
    root->left = bst_insert_recursively(root->left, x);
  } else if (x > root->data) {
    root->right = bst_insert_recursively(root->right, x);
  }
  return root;
}


void bst_erase(struct node *root, int x) {
  struct node *p = root, *parent;
  int left = 0;
  while (p && p->data != x) {
    parent = p;
    if (x < p->data) {
      p = p->left;
      left = 1;
    } else {
      p = p->right;
      left = 0;
    }
  }
  if (!p) {
    puts("element not exists!!!");
  } else {
    if (p->left && p->right) {
      struct node *q = bst_find_min(p->right);
      int tmp = p->data;
      p->data = q->data;
      q->data = tmp;

      bst_erase(p->right, tmp);
    } else {
      struct node *tmp;
      if (p->left)
        tmp = p->left;
      else if (p->right)
        tmp = p->right;
      else
        tmp = 0;

      if (left)
        parent->left = tmp;
      else {
        parent->right = tmp;
      }
      free(p);
    }
  }
}

static struct node *bst_find_min(struct node *root) {
  while (root && root->left)
    root = root->left;
  return root;
}

void bst_inorder(struct node *root) {
  if (root) {
    bst_inorder(root->left);
    printf("%d ", root->data);
    bst_inorder(root->right);
  }
}

void bst_preorder(struct node *root) {
  if (root) {
    printf("%d ", root->data);
    bst_preorder(root->left);
    bst_preorder(root->right);
  }
}
