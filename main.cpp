#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

using namespace std;

vector<int> global_vector;

struct node {
    int data;
    node* left;
    node* right;
};

class BST {
public:
    BST() {
        root = NULL;
    }
    node* root;
    node* insert(int val, node* n) {
        if (n == NULL) {
            n = new node;
            n->data = val;
            n->left = NULL;
            n->right = NULL;
        }
        else if (val < n->data) {
            n->left = insert(val, n->left);
        }
        else if (val > n->data) {
            n->right = insert(val, n->right);
        }
        return n;
    }
    node* find_min(node* n) {
        if (n == NULL) {
            return NULL;
        }
        else if (n->left == NULL) {
            return n;
        }
        else {
            return find_min(n->left);
        }
    }
    node* find_max(node* n) {
        if (n == NULL) {
            return NULL;
        }
        else if (n->right == NULL) {
            return n;
        }
        else {
            return find_max(n->right);
        }
    }
    node* remove(int val, node* n) {
        node* temp;
        if (n == NULL) {
            return NULL;
        }
        else if (val < n->data) {
            n->left = remove(val, n->left);
        }
        else if (val > n->data) {
            n->right = remove(val, n->right);
        }
        else if (val == n->data && n->left && n->right) {
            temp = find_max(n->left);
            n->data = temp->data;
            n->left = remove(temp->data, n->left);
        }
        else {
            temp = n;
            if (n->left == NULL) {
                n = n->right;
            }
            else if (n->right == NULL) {
                n = n->left;
            }
            delete temp;
        }
        return n;
    }
    void inorder(node* n) {
        if (n == NULL)
            return;
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }
    void preorder(node* n) {
        if (n == NULL)
            return;
        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void postorder(node* n) {
        if (n == NULL)
            return;
        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }
    node* find(int val, node* n) {
        if (n == NULL)
            return NULL;
        else if (val < n->data)
            return find(val, n->left);
        else if (val > n->data)
            return find(val, n->right);
        else
            return n;
    }
};




int main() {
    BST tree;

    string input_string;
    getline(cin, input_string);
    stringstream ss(input_string);
    int data;
    bool first_output = true;
    while (ss >> data) {
        tree.root = tree.insert(data, tree.root);
        if (first_output) {
            first_output = false;
        }
        else {
            //cout << " ";
        }
        //cout << data;
    }
    tree.inorder(tree.root);
    cout << endl;
    tree.postorder(tree.root);
    cout << endl;

    string avengers_input;
    getline(cin, avengers_input);
    first_output = true;




    return 0;
}