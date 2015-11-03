// Construct Binary Search Tree with preorder sequence.

// 1. give sequence q, traverse q from start
// 2. if seq[i] < seq[i-1], find the min node j before i that seq[j] > seq[i], let i be the left  child of j
// 3. if seq[i] > seq[i-1], find the max node j before i that seq[j] < seq[i], let i be the right child of j

// Time Complexity: O(n^2)

#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr) : val(v), left(l), right(r) {}
};
TreeNode* ConstructWithPreorder(const vector<int>& seq) {
  vector<TreeNode *> nodes;
  for (int i = 0; i != seq.size(); ++i)
    nodes.push_back(new TreeNode(seq[i]));

  if (nodes.empty())
    return nullptr;
  
  for (int i = 1; i != nodes.size(); ++i) {
    if (seq[i-1] > seq[i]) {
      int j = i-1, k = j;
      while (j >= 0) {
        if (seq[j] > seq[i] && seq[j] < seq[k])
          k = j;
        --j;
      }
      nodes[k]->left = nodes[i];
    } else if (seq[i-1] < seq[i]) {
      int j = i - 1, k = j;
      while (j >= 0) {
        if (seq[j] < seq[i] && seq[j] > seq[k])
          k = j;
        --j;
      }
      nodes[k]->right = nodes[i];
    }
  }
  return nodes[0];
}


// recursive solution
// Time Complexity
// T(n) = T(i-1) + T(n-i) + O(n)
// worst : T(n) = T(1) + T(n-2) + O(n) =====> O(n^2)
// average: T(n) = T(n/2) + T(n/2) + O(n) =====> O(nlgn)
TreeNode* ConstructTreeUtil(vector<int> seq, int low, int high) {
  // base case
  if (high < low)
    return nullptr;
  if (high == low)
    return new TreeNode(seq[low]);
  TreeNode* root = new TreeNode(seq[low]);

  // find the first element that greater than root->val, it splits the tree into left and right part.
  int i;
  for (i = low; i <= high; ++i)
    if (seq[i] > root->val)
      break;

  root->left = ConstructTreeUtil(seq, low+1, i-1);
  root->right = ConstructTreeUtil(seq, i, high);
  return root;
}

// O(n) recursively
// See BSTCheck.cc:BSTCheckHelper
// Time Complexity : T(n) = O(n), once an element

TreeNode* ConstructTree2(vector<int> seq, int& index, int min, int max) {
  if (index >= seq.size())
    return nullptr;
  TreeNode* root = nullptr;
  if (seq[index] > min && seq[index] < max) {
    root = new TreeNode(seq[index]);
    index += 1;
    root->left = ConstructTree2(seq, index, min, root->val);
    root->right = ConstructTree2(seq, index, root->val, max);
  }
  return root;
}

// O(n) with stack
// 1.create a stack
// 2. push first value into stack, make it as root
// 3. if next value less than stack's top value, push it into stack, make it be the left child of stack's top
// 4. else if next value greater than stack's top value, pop stack until it's empty or next value less than stack's top value
//     make the next value be the right child of last poped value, push next value into stack
// 5. repeat unitl there no elements in sequence.

// Time Complexity : O(n)
// every element will be push/pop at most once

TreeNode* ConstructWithStack(vector<int> seq) {
  if (seq.empty())
    return nullptr;
  stack<TreeNode*> s;
  TreeNode* root = new TreeNode(seq[0]);
  s.push(root);
  for (int i = 1; i != seq.size(); ++i) {
    TreeNode* cur = new TreeNode(seq[i]);
    TreeNode* top = s.top();
    if (cur->val < top->val) {
      top->left = cur;
      s.push(cur);
    } else {
      do {
        top = s.top();
        s.pop();
      } while (!s.empty() && s.top()->val < cur->val);
      top->right = cur;
      s.push(cur);
    }
  }
  return root;
}


int FindHelper(vector<int>, int, int, int);

// Time Complexity : O(n^2) worst case: only left/right child

// preorder: root-->left-->right
//          ------        -------
// inorder: |left|->root->|right|
//          ------        -------
// root in preorder splits inorder into 3 parts: left root right
TreeNode* ConstrcutTreeWithPreAndInorder(vector<int> preorder, int pl, int ph,
                                         vector<int> inorder, int il, int ih) {
  if (ih < il)
    return nullptr;
  if (ih == il)
    return new TreeNode(inorder[il]);
  TreeNode* root = new TreeNode(preorder[pl]);
  int i = FindHelper(inorder, il, ih, root->val);
  int left_len = i - il;
  int right_len = ih - i;
  root->left = ConstrcutTreeWithPreAndInorder(preorder, pl+1, pl+left_len,
                                              inorder, il, i-1);
  root->right = ConstrcutTreeWithPreAndInorder(preorder, pl+left_len+1, ph,
                                               inorder, i+1, ih);
  return root;
}

int FindHelper(vector<int> inorder, int low, int high, int x) {
  for (int i = low; i <= high; ++i)
    if (x == inorder[i])
      return i;
  return -1;
}

int FindHelper(vector<int> data, int x) {
  for (int i = 0; i != data.size(); ++i)
    if (x == data[i])
      return i;
  return -1;
}


// Construct Full binary tree with preorder and postorder sequence
// full tree: any node has 0 or 2 childs
TreeNode* ConstructFullWithPreAndPostorder(vector<int> preorder, int pre_low, int pre_high, vector<int> postorder) {
  if (pre_low > pre_high)
    return nullptr;
  if (pre_low == pre_high)
    return new TreeNode(preorder[pre_low]);
  
  TreeNode* root = new TreeNode(preorder[pre_low]);
  int index_in_postorder = FindHelper(postorder, root->val);
  int right_child_index_in_preorder = FindHelper(preorder, postorder[index_in_postorder-1]);
  root->left = ConstructFullWithPreAndPostorder(preorder, pre_low+1, right_child_index_in_preorder-1, postorder);
  root->right = ConstructFullWithPreAndPostorder(preorder, right_child_index_in_preorder, pre_high, postorder);
  return root;
}

void BSTInorder(TreeNode* root) {
  if (root) {
    BSTInorder(root->left);
    cout << root->val << " ";
    BSTInorder(root->right);
  }
}

void BSTPostOrder(TreeNode* root) {
  if (root) {
    BSTPostOrder(root->left);
    BSTPostOrder(root->right);
    cout << root->val << ' ';
  }
}

void Shuffle(vector<int>& seq) {
  srand(time(nullptr));
  for (int i = seq.size()-1; i > 0; --i) {
    int j = rand() % (i+1);
    using std::swap;
    swap(seq[i], seq[j]);
  }
}

int main() {
  {
    vector<int> seq = {10, 5, 1, 7, 40, 50};
    TreeNode* root = ConstructTreeUtil(seq, 0, seq.size()-1);
    BSTInorder(root);
    cout << '\n';
  }
  {
    vector<int> seq = {20, 10, 5, 1, 7, 15, 30, 25, 35, 40};
    int index = 0;
    TreeNode* root = ConstructTree2(seq, index, numeric_limits<int>::min(), numeric_limits<int>::max());
    BSTInorder(root);
    cout << '\n';
  }
  {
    vector<int> seq = {20, 15, 10, 13, 12, 14, 25, 35, 30};
    TreeNode* root = ConstructWithStack(seq);
    BSTInorder(root);
    cout << '\n';
  }

  {
    vector<int> preorder = {1, 2, 4, 5, 7, 3, 6};
    vector<int> inorder = {4, 2, 5, 7, 1, 6, 3};
    TreeNode* root = ConstrcutTreeWithPreAndInorder(preorder, 0, preorder.size()-1,
                                                    inorder, 0, inorder.size()-1);
    BSTPostOrder(root);
    cout << '\n';
  }
  {
    vector<int> preorder = {1, 2, 3, 4, 5, 6, 7};
    vector<int> postorder = {2, 4, 6, 7, 5, 3, 1};
    TreeNode* root = ConstructFullWithPreAndPostorder(preorder, 0, preorder.size()-1, postorder);
    BSTInorder(root);
    cout << '\n';
  }
  {
    vector<int> preorder = {1};
    vector<int> postorder = {1};
    TreeNode* root = ConstructFullWithPreAndPostorder(preorder, 0, preorder.size()-1, postorder);
    BSTInorder(root);
    cout << '\n';
  }

  {
    vector<int> preorder = {1, 2, 3};
    vector<int> postorder = {2, 3, 1};
    TreeNode* root = ConstructFullWithPreAndPostorder(preorder, 0, preorder.size()-1, postorder);
    BSTInorder(root);
    cout << '\n';
  }
  
  return 0;
}
