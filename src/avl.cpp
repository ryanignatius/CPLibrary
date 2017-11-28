#include <bits/stdc++.h>

using namespace std;

typedef int dataType;

class Node {
    public:
        dataType key;
        Node *left;
        Node *right;
        Node *prev;
        Node *next;
        int height;

        Node(dataType k){
            key = k;
            left = NULL;
            right = NULL;
            prev = NULL;
            next = NULL;
            height = 1;
        }
};

class AVL {
    private:
        Node *root;
        Node *first;
        Node *last;
        Node *temp;
        Node *tempPrev;
        Node *tempNext;

        int getNodeHeight(Node *N) {
            if (N == NULL) {
                return 0;
            } else {
                return N->height;
            }
        }
        
        int getBalance(Node *N) {
            if (N == NULL) {
                return 0;
            } else {
                return getNodeHeight(N->left) - getNodeHeight(N->right);
            }
        }
        
        Node *rightRotate(Node *y) {
            Node *x = y->left;
            Node *T2 = x->right;

            // rotate
            x->right = y;
            y->left = T2;

            // update height
            y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
            x->height = max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
            
            // return new root
            return x;
        }

        Node *leftRotate(Node *x) {
            Node *y = x->right;
            Node *T2 = y->left;

            // rotate
            y->left = x;
            x->right = T2;

            // update height
            x->height = max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
            y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
            
            // return new root
            return y;
        }

        Node* insert(Node *node, int key) {
            // 1. Perform the normal BST insertion
            if (node == NULL) {
                temp = new Node(key);
                temp->prev = tempPrev;
                temp->next = tempNext;
                if (tempPrev == NULL && tempNext == NULL) {
                    first = temp;
                    last = temp;
                } else {
                    if (tempPrev != NULL) tempPrev->next = temp;
                    else first = temp;
                    if (tempNext != NULL) tempNext->prev = temp;
                    else last = temp;
                }
                return temp;
            }
            if (key < node->key) {
                tempNext = node;
                node->left = insert(node->left, key);
            } else if (key > node->key) {
                tempPrev = node;
                node->right = insert(node->right, key);
            } else {
                // key already exists
                return node;
            }

            // 2. Update height of this ancestor node
            node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));

            // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
            int balance = getBalance(node);

            // If this node becomes unbalanced, then
            // there are 4 cases

            // Left Left Case
            if (balance > 1 && key < node->left->key) {
                return rightRotate(node);
            }

            // Right Right Case
            if (balance < -1 && key > node->right->key) {
                return leftRotate(node);
            }

            // Left Right Case
            if (balance > 1 && key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // Right Left Case
            if (balance < -1 && key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            /* return the (unchanged) node pointer */
            return node;
        }

        void preOrder(Node *node) {
            if (node != NULL) {
                printf("%d ", node->key);
                preOrder(node->left);
                preOrder(node->right);
            }
        }

    public:
        AVL() {
            root = NULL;
            first = NULL;
            last = NULL;
        }
        Node* begin() {
            return first;
        }
        Node* end() {
            return last;
        }
        
        void insert(int key) {
            tempPrev = NULL;
            tempNext = NULL;
            root = insert(root, key);
        }
        void preOrder() {
            preOrder(root);
        }
};

int main(){
    AVL avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.insert(10);

/* The constructed AVL Tree would be
        30
       /  \
     20   40
    /  \     \
   10  25    50
*/
    avl.preOrder();
    cout << endl;
    for (Node* node = avl.begin(); node != NULL; node = node->next){
        cout << node->key << endl;
    }
    return 0;
}

