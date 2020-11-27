#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

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
    vector<int> levels;
    int current_level;
    int seperate_level;
    int s_counter;
    int v_counter;
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
        cout << n->data << ", ";
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
        //cout << n->data << " ";
        global_vector.push_back(n->data);
    }
    void levelorder() {
        queue<node*> q_current;
        queue<node*> q_next;
        q_current.push(root);
        current_level = 0;
        levels.clear();

        while (!q_current.empty()) {
            //iterate current level
            //cout << "current level " << current_level << ": ";
            while (!q_current.empty()) {
                node* current_node = q_current.front();
                q_current.pop();
                if (levels.size() < current_level + 1) {
                    levels.push_back(0);
                }
                levels[current_level] += 1;
                //cout << current_node->data << " ";
                if (current_node->left != NULL) {
                    q_next.push(current_node->left);
                }
                if (current_node->right != NULL) {
                    q_next.push(current_node->right);
                }
            }
            //cout << endl;
            //assign the next queue to current queue
            q_current = q_next;
            //clear the next queue
            std::queue<node*> empty;
            std::swap(q_next, empty);
            current_level += 1;
        }

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
    
    void find_seperate_level() {
        int left_sum;
        int right_sum;
        int min_diff = 2147483647;
        
        seperate_level = 0;

        for (int mid = 0; mid < levels.size() - 1; ++mid) {
            //cout << "current line " << mid << endl;
            left_sum = 0;
            right_sum = 0;
            for (int left = 0; left < mid + 1; ++left) {
                left_sum += levels[left];
            }
            for (int right = mid+1; right < levels.size(); ++right) {
                right_sum += levels[right];
            }
            int current_diff = abs(left_sum - right_sum);
            //cout << "current diff: " << current_diff << endl;
            //cout << "left sum: " << left_sum << endl;
            //cout << "right sum: " << right_sum << endl << endl;
            if (current_diff < min_diff) {
                //cout << "current diff: " << current_diff << endl;
                //cout << "left sum: " << left_sum << endl;
                //cout << "right sum: " << right_sum << endl;
                min_diff = current_diff;
                seperate_level = mid;
            }
        }
        //cout << "mid: " << seperate_level << endl;
    }

    void print_survivors(node* n, int current_level) {
        if (n == NULL)
            return;
        print_survivors(n->left, current_level + 1);
        if (current_level > seperate_level) {
            //don't print
        }
        else {
            //cout << n->data << " ";
            //cout << "level: " << current_level << ", " << n->data << endl;
            global_vector.push_back(n->data);
        }
        s_counter++;
        print_survivors(n->right, current_level + 1);
    }

    void print_victims(node* n, int current_level) {
        if (n == NULL)
            return;
        if (current_level <= seperate_level) {
            //don't print
        }
        else {
            v_counter++;
            //cout << n->data << " ";
            //cout << "level: " << current_level << ", " << n->data << endl;
            global_vector.push_back(n->data);
        }
        print_victims(n->left, current_level + 1);
        print_victims(n->right, current_level + 1);
    }

};




int main() {
    BST tree;
    vector<int> avengers;

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
    //tree.inorder(tree.root);

    global_vector.clear();
    tree.postorder(tree.root);
    for (int i = 0; i < global_vector.size(); ++i) {
        if (i != 0) {
            cout << " ";
        }
        cout << global_vector[i];
    }
    cout << endl;

    ss.str("");
    ss.clear();
    string avengers_input;
    getline(cin, avengers_input);
    ss << avengers_input;
    while (ss >> data) {
        avengers.push_back(data);
    }

    //delete avengers
    for (int i = 0; i < avengers.size(); ++i) {
        tree.root = tree.remove(avengers[i], tree.root);
    }

    //level order traveral
    tree.levelorder();
    for (int i = 0; i < tree.levels.size(); ++i) {
        //cout << "level " << i << " : " << tree.levels[i] << endl;
    }

    //find the line that seperate survivors and victims
    tree.find_seperate_level();

    //print survivors
    global_vector.clear();
    tree.print_survivors(tree.root, 0);
    for (int i = 0; i < global_vector.size(); ++i) {
        if (i != 0) {
            cout << " ";
        }
        cout << global_vector[i];
    }
    cout << endl;

    //print victims
    global_vector.clear();
    tree.print_victims(tree.root, 0);
    for (int i = 0; i < global_vector.size(); ++i) {
        if (i != 0) {
            cout << " ";
        }
        cout << global_vector[i];
    }

    //cout << "s: " << tree.s_counter << endl;
    //cout << "v: " << tree.v_counter << endl;

    return 0;
}