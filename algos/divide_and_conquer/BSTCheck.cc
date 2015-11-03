// Binary Search Tree check
//
// Inorder Traverse
// 
// Time Complexity: O(n)

#include <iostream>
#include <ios>
#include <limits>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool IsBSTHelper(TreeNode*, TreeNode* &);

bool IsBST(TreeNode* root) {
  TreeNode *pre = nullptr;
  return IsBSTHelper(root, pre);
}

bool IsBSTHelper(TreeNode* root, TreeNode* &pre) {
  if (!root)
    return true;
  if (!IsBSTHelper(root->left, pre))
    return false;
  if (pre && root->val <= pre->val)
    return false;
  pre = root;
  return IsBSTHelper(root->right, pre);
}

bool BSTCheckHelper(TreeNode*, int, int);

bool BSTCheck(TreeNode* root) {
  return BSTCheckHelper(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

//       A    A                A                   A
//      /      \              /                     \
//     B        B            B                       B
//    /          \            \                      /
//   C            C            C                    C

// 1. C's val less than B
// 2. C's val greater than B
// 3. C's val greater than B, less than A
// 4. C's val less than B, greater than A
bool BSTCheckHelper(TreeNode* root, int min, int max) {
  if (!root)
    return true;
  if (root->val < min || root->val > max)
    return false;
  return BSTCheckHelper(root->left, min, root->val-1) &&
    BSTCheckHelper(root->right, root->val+1, max);
}

int main() {
  TreeNode* root = new TreeNode(3);
  root->left = new TreeNode(2);
  root->right = new TreeNode(5);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(4);

  cout << boolalpha << IsBST(root) << '\n';
  cout << BSTCheck(root) << '\n';
  return 0;
}


