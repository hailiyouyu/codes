#include "../binary_search_tree.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <ctime>
#include <cstdlib>

int main() {
  using namespace std;
  srand(time(0));

  vector<int> data;
  for (int i = 0; i != 10; ++i) {
    data.push_back(rand() % 100);
  }

  copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
  cout << "\n\n";
  struct node *root = 0;
  for (int i = 0; i != 10; ++i) {
    root = bst_insert(root, data[i]);
  }

  bst_inorder(root);
  cout << '\n';
  bst_preorder(root);
  cout << '\n';

  bst_erase(root, data[2]);
  bst_inorder(root);
  cout << '\n';
  bst_preorder(root);
  cout << '\n';
  return 0;
}
