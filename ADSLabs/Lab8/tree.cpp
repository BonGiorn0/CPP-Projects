#include <iostream>

struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;
    size_t vowelCount = 0;
    char thirdVowel = 0;

public:
    BinaryTree() : root(nullptr) {}

    void insert(char value) {
        root = insertRecursive(root, value);
    }

    void printInOrder() {
        printInOrderRecursive(root);
    }

    void printThirdVowel() {
        if(thirdVowel == 0)
            std::cout << "theres no third vowel";
        else
            std::cout << "The third vowel is: " << thirdVowel;
        std::cout << '\n';
    }

    void findParentAndChildren(char key) {
        findParentAndChildrenRecursive(root, key, nullptr);
    }

    TreeNode* findKey(char key) {
        return findKeyRecursive(root, key, nullptr);
    }

private:
    TreeNode* insertRecursive(TreeNode* current, char value) {
        if (current == nullptr) {
            if (value == 'a' | value == 'o' | value == 'e' | value == 'i' | value == 'u' |
                value == 'A' | value == 'O' | value == 'E' | value == 'I' | value == 'U')
                vowelCount++;

            if (vowelCount == 3)
                thirdVowel = value;
            return new TreeNode(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }

        

        return current;
    }

        void findParentAndChildrenRecursive(TreeNode* current, char key, TreeNode* parent) {
        if (current == nullptr) {
            std::cout << "Key not found in the tree." << std::endl;
            return;
        }

        if (current->data == key) {
            std::cout << "Key: " << key << std::endl;

            if (parent != nullptr) {
                std::cout << "Parent: " << parent->data << std::endl;
            } else {
                std::cout << "No parent (root node)." << std::endl;
            }

            if (current->left != nullptr) {
                std::cout << "Left child: " << current->left->data << std::endl;
            } else {
                std::cout << "No left child." << std::endl;
            }

            if (current->right != nullptr) {
                std::cout << "Right child: " << current->right->data << std::endl;
            } else {
                std::cout << "No right child." << std::endl;
            }
            return;
        }

        findParentAndChildrenRecursive(current->left, key, current);
        findParentAndChildrenRecursive(current->right, key, current);
    }

    TreeNode* findKeyRecursive(TreeNode* current, char key, TreeNode* parent) {
        if (current == nullptr) {
            return nullptr; // Key not found in the tree
        }

        if (current->data == key) {
            return current;
        }

        TreeNode* leftResult = findKeyRecursive(current->left, key, current);
        if (leftResult != nullptr) {
            return leftResult;
        }

        return findKeyRecursive(current->right, key, current);
    }

    void printInOrderRecursive(TreeNode* current) {
        if (current != nullptr) {
            printInOrderRecursive(current->left);
            std::cout << current->data << " ";
            printInOrderRecursive(current->right);
        }
    }
};

int main() {
    BinaryTree tree;

    tree.insert('d');
    tree.insert('b');
    tree.insert('c');
    tree.insert('d');
    tree.insert('e');
    tree.insert('f');
    tree.insert('g');
    tree.insert('i');
    tree.insert('o');

    tree.printThirdVowel();
    tree.findParentAndChildren('f');
    TreeNode *node = tree.findKey('d');
    
    if(node == NULL){
        std::cout << "Not found" << '\n';
    }else{
        std::cout << "Is in tree" << '\n';
    }

    std::cout << "In-Order Traversal: ";
    tree.printInOrder();
    std::cout << std::endl;

    return 0;
}
