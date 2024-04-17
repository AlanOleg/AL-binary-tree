#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    int balance;
    Node* left;   // smaller
    Node* right;  // bigger
    Node* previous;
};

class BSTree {
public:
    Node* root;
public:
    BSTree();
    BSTree(vector<int> vector);
    ~BSTree();
    bool add_element(int value);
    bool delete_element(int value);
    bool find_element(int value);
    bool rebalance(Node* old_node);
    void print();
    bool save_to_file(const string& path);
    bool load_from_file(const string& path);
};

BSTree::BSTree() {
    root = nullptr;
}

BSTree::BSTree(vector<int> vector) {
    root = nullptr;
    for (int i = 0; i < vector.size(); i++) {
        add_element(vector[i]);
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
    Node* new_node = new Node{value, 0, nullptr, nullptr, nullptr};
    if (root == nullptr) {
        root = new_node;
        return true;
    }
    else {
        Node* current = root;
        while (not((new_node->data > current->data and current->right == nullptr) or (new_node->data < current->data and current->left == nullptr))) {
            if (new_node->data > current->data) {
                current->balance += 1;
                current = current->right;
            }
            else if (new_node->data < current->data) {
                current->balance -= 1;
                current = current->left;
            }
            else {
                return false;
            }
        }
        if (new_node->data > current->data and current->right == nullptr) {
            current->balance += 1;
            current->right = new_node;
        }
        else {
            current->balance -= 1;
            current->left = new_node;
        }
        new_node->previous = current;
        if (current->previous != nullptr) {
            rebalance(current->previous);
        }
        return true;
    }
}

bool BSTree::rebalance(Node* old_node) {
    if (old_node->balance > 1) {
        Node* current = old_node->right;
        while (current->left != nullptr) {
            current = current->left;
        } // сделать иф для когда 1-2-3 просто со смещением
        current->previous->left = current->right;
        if (current->right != nullptr) {
            current->right->previous = current->previous;
        }
        current->previous->balance += 1;
        rebalance(current->previous);

        if (old_node == root) {
            current = root;
        }
        current->right = old_node->right;
        current->left = old_node;
        current->previous = old_node->previous;
        current->balance = old_node->balance - 2;
        old_node->previous = current;
        old_node->right = nullptr;
        if (old_node->left == nullptr) {  // Костыль ГОСТ Р 58281-2022
            old_node->balance = 0;
        }
        else if (old_node->left->left == nullptr and old_node->left->right) {
            old_node->balance = -1;
        }
        else {
            old_node->balance = -2;
            rebalance(old_node);
        }
        rebalance(current);
        return true;
    }
    else if (old_node->balance < 1) {
        Node* current = old_node->left;
        while (current->right != nullptr) {
            current = current->right;
        }
        current->previous->right = current->left;
        if (current->right != nullptr) {
            current->left->previous = current->previous;
        }
        current->previous->balance -= 1;
        rebalance(current->previous);

        if (old_node == root) {
            current = root;
        }
        current->left = old_node->left;
        current->right = old_node;
        current->previous = old_node->previous;
        current->balance = old_node->balance + 2;
        old_node->previous = current;
        old_node->left = nullptr;
        if (old_node->right == nullptr) {  // Костыль ГОСТ Р 58281-2022
            old_node->balance = 0;
        }
        else if (old_node->right->right == nullptr and old_node->right->left) {
            old_node->balance = 1;
        }
        else {
            old_node->balance = 2;
            rebalance(old_node);
        }
        rebalance(current);
        return true;
    }
    return false;
}

void BSTree::print() {
    cout << "test\n";
}

int main() {
    vector<int> vector = {1, 2, 3};
    BSTree drevo(vector);
    drevo.print();
}
