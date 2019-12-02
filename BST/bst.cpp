// Simple Binary Search Tree program
#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct BstNode {
  string data;
  BstNode* left;
  BstNode* right;
};

// Do not work for all cases
bool after(const string& s1, const string& s2) {
  for (size_t i = 0; i < s1.size() && i < s2.size(); ++i) {
    if (tolower(s1[i]) != tolower(s2[i]))
      return tolower(s1[i]) > tolower(s2[i]);
  }
  return s1.size() > s2.size();
}

string searchMin(BstNode* root) {
  if (!root)  return "Empty tree!";

  return root->left ? searchMin(root->left) : root->data;
}

string searchMax(BstNode* root) {
  if (!root)  return "Empty tree!";

  return root->right ? searchMin(root->right) : root->data;
}

BstNode* insert(BstNode* root, const string& data) {
  if (!root) {
    root = new BstNode();
    root->data = data;
    root->left = root->right = nullptr;
    //cout << "Root (Node): " << root->data << "\n";
  } else if (after(data, root->data)) {
    root->right = insert(root->right, data);
    //cout << "Right subtree: " << root->right->data << "\n";
  } else if (after(root->data, data)) {
    root->left = insert(root->left, data);
    //cout << "Left subtree: " << root->left->data << "\n";
  }
  return  root;
}

BstNode* minNode(BstNode* root) {
  while (!root) {
    root = root->right;
  }
  return root;
}

BstNode* remove(BstNode* root, const string& data) {
  if (!root) {
    return root;
  } else if (after(root->data, data)) {
    root->left = remove(root->left, data);
  } else if (after(data, root->data)) {
    root->right = remove(root->right, data);
  } else {
    if (!root->left && !root->right) {
      delete root;
      root = nullptr;
    } else if (root->left) {
      BstNode* temp = root;
      root = root->left;
      delete temp;
    } else if (root->right) {
      BstNode* temp = root;
      root = root->right;
      delete temp;
    } else {
      BstNode* temp = minNode(root->right);
      root->data = temp->data;
      root->right = remove(root->right, temp->data);
    }
  }
  return root;
}

bool search(BstNode* root, const string& str) {
  if (!root)
    return false;
  else if (!after(root->data, str) && !after(str, root->data))
    return true;
  else if (after(root->data, str))
    return search(root->left, str);
  else if (!after(root->data, str))
    return search(root->right, str);
}

// in-order
void dfs(BstNode* root) {
  if (root) {
    dfs(root->left);
    cout << root->data << " ";
    dfs(root->right);
  }
}

void bfs(BstNode* root) {
  if (!root)  cout << "Error: empty tree";
  queue<BstNode*> q;
  q.push(root);

  while(!q.empty()) {
    BstNode* current = q.front();
    q.pop();

    cout << current->data << " ";
    if (current->left)
        q.push(current->left);
    if (current->right)
        q.push(current->right);
  }    
}

int main() {
  string s1 = "Astana";
  string s2 = "Astan";
  if (after(s2, s1))
      cout << "After\n";
  else
      cout << "Before\n";

  BstNode *root = nullptr;
  root = insert(root, "asd"); 
  root = insert(root, "aaasd");
  root = insert(root, "bsdfg");
  root = insert(root, "qwe");
  root = insert(root, "zxc");
  root = remove(root, "aaasd");
  
  dfs(root);
  cout << "\n";
  
  bfs(root);
  cout << "\n";

  cout << searchMin(root) << "\n";

  if (search(root,"zxc"))
      cout<<"Found\n";
  else
      cout<<"Not Found\n";
      
  return 0;
}
