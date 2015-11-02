#include "avl_tree.h"

#include <iostream>
#include <cstdlib>

static bool avl_balanced(struct node *p);
static int avl_height(struct node *p);
static struct node *avl_ll_rotate(struct node *p);
static struct node *avl_rr_rotate(struct node *p);
static struct node *avl_lr_rotate(struct node *p);
static struct node *avl_rl_rotate(struct node *p);

struct node *avl_find(struct node *root, int x) {
  while (root && x != root->data) {
    if (x < root->data)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

struct node *avl_find_recursively(struct node *root, int x) {
  if (!root || root->data == x)
    return root;
  if (x < root->data)
    return avl_find_recursively(root->left, x);
  else
    return avl_find_recursively(root->right, x);
}

struct node *avl_insert(struct node *root, int x) {
  struct node *p = root;
  if (!p) {
    p = (struct node *)malloc(sizeof(struct node));
    p->data = x;
    p->height = 0;
    p->left = p->right = 0;
  } else if (x < p->data) {
    p->left = avl_insert(p->left, x);
    if (!avl_balanced(p)) {
      if (x < p->left->data)
        p = avl_ll_rotate(p);
      else if (x > p->left->data)
        p = avl_lr_rotate(p);
    } 
  } else if (x > p->data) {
    p->right = avl_insert(p->right, x);
    if (!avl_balanced(p)) {
      if (x > p->right->data)
        p = avl_rr_rotate(p);
      else if (x < p->right->data)
        p = avl_rl_rotate(p);
    }
  }
  p->height = max(avl_height(p->left), avl_height(p->right)) + 1;
  return p;
}

struct node *avl_erase(struct node *root, int x) {
  struct node *p = root;
  if (x < p->data) {
    p->left = avl_erase(p->left, x);
    if (!avl_balanced(p)) {
      if (avl_height(p->right->left) > avl_height(p->right->right))
        p = avl_rl_rotate(p);
      else
        p = avl_rr_rotate(p);
    }
  } else if (x > p->data) {
    p->right = avl_erase(p->right, x);
    if (!avl_balanced(p)) {
      if (avl_height(p->left->right) > avl_height(p->left->left))
        p = avl_lr_rotate(p);
      else
        p = avl_ll_rotate(p);
    }
  } else {
    if (p->left && p->right) {
      struct node *right_min = avl_find_min(p->right);
      p->data = right_min->data;

      p->right = avl_erase(p->right, right_min->data);
      if (!avl_balanced(p)) {
        if (avl_height(p->left->right) > avl_height(p->left->left))
          p = avl_lr_rotate(p);
        else
          p = avl_ll_rotate(p);
      }
    } else {
      struct node *tmp;
      if (!p->left)
        tmp = p->right;
      else
        tmp = p->left;
      free(p);
      p = tmp;
    }
  }
  if (!p) {
    p->height = max(avl_height(p->left), avl_height(p->right)) + 1;    
  }
  return p;
}

static bool avl_balanced(struct node *p) {
  int diff;
  if (!p)
    return true;
  diff = avl_height(p->left) - avl_height(p->right);
  if (diff <= 1 && diff >= -1)
    return true;
  return false;
}

static int avl_height(struct node *p) {
  if (p)
    return p->height;
  else
    return -1;
}

static struct node *avl_ll_rotate(struct node *p) {
  struct node *q = p->left;
  p->left = q->right;
  q->right = p;

  p->height = max(avl_height(p->left), avl_height(p->right)) + 1;
  q->height = max(avl_height(q->left), avl_height(q->right)) + 1;
  return q;
}

static struct node *avl_rr_rotate(struct node *p) {
  struct node *q = p->right;
  p->right = q->left;
  q->left = p;

  p->height = max(avl_height(p->left), avl_height(p->right)) + 1;
  q->height = max(avl_height(q->left), avl_height(q->right)) + 1;
  return q;
}

static struct node *avl_lr_rotate(struct node *p) {
  struct node *q = p->left;
  p->left = avl_rr_rotate(q);
  return avl_ll_rotate(p);
}

static struct node *avl_rl_rotate(struct node *p) {
  struct node *q = p->right;
  p->right = avl_ll_rotate(q);
  return avl_rr_rotate(p);
}
