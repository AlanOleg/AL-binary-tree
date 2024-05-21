#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;   // smaller
    Node* right;  // bigger
    Node* previous = nullptr;
};

class BSTree {
public:
    Node* root = nullptr;
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
}

BSTree::BSTree(initializer_list<int> list) {
    for (auto i: list) {
        add_element(i);
    }
}

BSTree::~BSTree() {
    Node* current = root;
    while (current != nullptr) {
        while (not(current->left == nullptr and current->right == nullptr)) {
            while (current->left != nullptr) {
                current = current->left;
            }
            while (current->right != nullptr) {
                current = current->right;
            }
        }
        Node* to_be_deleted = current;
        current = current->previous;
        if (current != nullptr and current->right == to_be_deleted) {
            current->right = nullptr;
        }
        else if (current != nullptr and current->left == to_be_deleted) {
            current->left = nullptr;
        }
        delete to_be_deleted;
    }
}

bool BSTree::add_element(int data) {
    Node* new_node = new Node{data, nullptr, nullptr, nullptr};
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

bool BSTree::delete_element(int data) {
    Node* current = root;
    while (not(current == nullptr)) {
        if (data > current->data) {
            current = current->right;
        }
        else if (data < current->data) {
            current = current->left;
        }
        else {
            current->right->previous = current->previous;
            if (current->previous != nullptr) {
                if (current == current->previous->right) {
                    current->previous->right = current->right;
                }
                else {
                    current->previous->left = current->right;
                }
            }
            Node* left_edge = current->right;
            while (left_edge->left != nullptr) {
                left_edge = left_edge->left;
            }
            current->left->previous = left_edge->left;
            left_edge->left = current->left;
            delete current;
            return true;
        }
    }
    return false;
}

bool BSTree::find_element(int data) {
    Node* current = root;
    while (not(current == nullptr)) {
        if (data > current->data) {
            current = current->right;
        }
        else if (data < current->data) {
            current = current->left;
        }
        else {
            return true;
        }
    }
    return false;
}

string print_recursion(Node* current){
    if (current == nullptr) {
        return " ";
    }
    if (current->left == nullptr and current->right == nullptr) {
        return to_string(current->data);
    }
    return to_string(current->data) + '(' + print_recursion(current->left) + ';' + print_recursion(current->right) + ')';
}

string print_to_file_recursion(Node* current) {
    if (current == nullptr) {
        return " ";
    }
    if (current->left == nullptr and current->right == nullptr) {
        return to_string(current->data);
    }
    return to_string(current->data) + ' ' + print_to_file_recursion(current->left) +  ' ' + print_to_file_recursion(current->right);
}

void BSTree::print() {
    cout << print_recursion(root) << endl;
}

bool BSTree::save_to_file(const string& path) {
    ofstream file_output("output.txt");
    if (file_output.is_open()) {
        file_output << print_to_file_recursion(root) << endl;
        file_output.close();
        return true;
    }
    else {
        cout << "Output file didn't open." << endl;
        return false;
    }
}

bool BSTree::load_from_file(const string& path) {
    ifstream file_input("input.txt");
    if (file_input.is_open()) {
        string data;
        while (file_input >> data) {
            this->add_element(stoi(data));
        }
        file_input.close();
        return true;
    }
    else {
        cout << "Input file didn't open." << endl;
        return false;
    }
}

int main() {
    ofstream file_output("output.txt");
    file_output.close();
    ifstream file_input("input.txt");
    BSTree drevo;
    drevo.load_from_file("input.txt");
    /*initializer_list<int> list = {4, 2, 6, 1, 3, 5, 7};
    BSTree drevo(list);*/
    drevo.print();
    drevo.save_to_file("output.txt");
}
