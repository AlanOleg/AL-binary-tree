#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;   // smaller
    Node* right;  // bigger
    Node* previous;
};

class BSTree {
public:
    Node* root;
public:
    BSTree();
    BSTree(initializer_list<int> list);
    ~BSTree();
    bool add_element(int value);
    bool delete_element(int value);
    bool find_element(int value);
    void print();
    bool save_to_file(const string& path);
    bool load_from_file(const string& path);
};

BSTree::BSTree() {
    root = nullptr;
}

BSTree::BSTree(initializer_list<int> list) {
    root = nullptr;
    for (auto i: list) {
        add_element(i);
    }
}

BSTree::~BSTree() {
    if (root == nullptr) {
    }
    else {
        Node* current = root;
        while (not(current == root and current->left == nullptr and current->right == nullptr)) {
            while (current->left != nullptr) {
                current = current->left;
            }
            while (current->right != nullptr) {
                current = current->right;
            }
            current = current->previous;
            if (current->left != nullptr) {
                delete current->left;
                current->left = nullptr;
            }
            if (current->right != nullptr) {
                if (not(current == root and (current->right->left != nullptr or current->right->right != nullptr))) {
                    delete current->right;
                    current->right = nullptr;
                }
            }
        }
        delete current;
    }
}

bool BSTree::add_element(int value) {
    Node* new_node = new Node{value, 0, nullptr, nullptr};
    if (root == nullptr) {
        root = new_node;
        return true;
    }
    else {
        Node* current = root;
        while (not((new_node->data > current->data and current->right == nullptr) or (new_node->data < current->data and current->left == nullptr))) {
            if (new_node->data > current->data) {
                current = current->right;
            }
            else if (new_node->data < current->data) {
                current = current->left;
            }
            else {
                return false;
            }
        }
        if (new_node->data > current->data and current->right == nullptr) {
            current->right = new_node;
        }
        else {
            current->left = new_node;
        }
        new_node->previous = current;
        return true;
    }
}

void BSTree::print() {
    cout << "test\n";
}

int main() {
    initializer_list<int> list = {1, 2, 3};
    BSTree drevo(list);
    drevo.print();
}

// 2        2^(depth-1)-1
//1 3
//
//   5
// 2   7
//1 3 6 8
//
//       1
//   1       1
// 1   1   1   1
//1 1 1 1 1 1 1 1