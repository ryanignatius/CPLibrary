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
        int size;

        Node(dataType k){
            key = k;
            left = NULL;
            right = NULL;
            prev = NULL;
            next = NULL;
            height = 1;
            size = 1;
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

        int getNodeSize(Node *N) {
            if (N == NULL) {
                return 0;
            } else {
                return N->size;
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

            // update size
            y->size = getNodeSize(y->left) + getNodeSize(y->right) + 1;
            x->size = getNodeSize(x->left) + getNodeSize(x->right) + 1;
            
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

            // update size
            x->size = getNodeSize(x->left) + getNodeSize(x->right) + 1;
            y->size = getNodeSize(y->left) + getNodeSize(y->right) + 1;
            
            // return new root
            return y;
        }

        Node* find(Node *node, dataType key) {
            if (node == NULL) return NULL;
            if (key == node->key) {
                return node;
            } else if (key < node->key) {
                return find(node->left, key);
            } else if (key > node->key) {
                return find(node->right, key);
            }
        }

        Node* insert(Node *node, dataType key) {
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
            node->size = 1 + getNodeSize(node->left) + getNodeSize(node->right);

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

        Node* remove(Node* node, dataType key) {
            // STEP 1: PERFORM STANDARD BST DELETE
            if (node == NULL) return node;
            if (key < node->key) {
                temp = node;
                node->left = remove(node->left, key);
            } else if (key > node->key) {
                temp = node;
                node->right = remove(node->right, key);
            } else {
                // node with only one child or no child
                if (node->left == NULL || node->right == NULL) {
                    Node *tempNode = node->left ? node->left : node->right;
                    // No child case
                    if (tempNode == NULL) {
                        if (node->next != NULL) {
                            node->next->prev = node->prev;
                        } else {
                            last = node->prev;
                        }
                        if (node->prev != NULL) {
                            node->prev->next = node->next;
                        } else {
                            first = node->next;
                        }
                        node = NULL;
                        free(node);
                    } else {// One child case
                        if (temp != NULL) {
                            if (temp->left == node) {
                                temp->left = tempNode;
                            } else if (temp->right == node) {
                                temp->right = tempNode;
                            }
                        }
                        if (node->next != NULL) {
                            node->next->prev = node->prev;
                        } else {
                            last = node->prev;
                        }
                        if (node->prev != NULL) {
                            node->prev->next = node->next;
                        } else {
                            first = node->next;
                        }
                        node = NULL;
                        free(node);
                        node = tempNode;
                    }
                } else {
                    // node with two children
                    Node* tempNode = node->next;
                    node->key = tempNode->key;
                    node->next = tempNode->next;
                    node->right = remove(node->right, tempNode->key);
                }
            }

            // If the tree had only one node then return
            if (node == NULL) return node;

            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
            node->size = 1 + getNodeSize(node->left) + getNodeSize(node->right);

            // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
            // check whether this node became unbalanced)
            int balance = getBalance(node);

            // If this node becomes unbalanced, then there are 4 cases

            // Left Left Case
            if (balance > 1 && getBalance(node->left) >= 0) {
                return rightRotate(node);
            }

            // Left Right Case
            if (balance > 1 && getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // Right Right Case
            if (balance < -1 && getBalance(node->right) <= 0) {
                return leftRotate(node);
            }

            // Right Left Case
            if (balance < -1 && getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        Node* getElement(Node* node, int k) {
            int leftSize = getNodeSize(node->left) + 1;
            if (k == leftSize) {
                return node;
            } else if (k < leftSize) {
                return getElement(node->left, k);
            } else if (k > leftSize) {
                return getElement(node->right, k-leftSize);
            }
            return NULL;
        }

        void preOrder(Node *node) {
            if (node != NULL) {
                printf("Key: %d, Height: %d, Size: %d\n", node->key, node->height, node->size);
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
        int size() {
            return getNodeSize(root);
        }
        
        Node* find(dataType key) {
            return find(root, key);
        }
        void insert(dataType key) {
            tempPrev = NULL;
            tempNext = NULL;
            root = insert(root, key);
        }
        void remove(dataType key) {
            temp = NULL;
            root = remove(root, key);
            if (root == NULL) {
                first = NULL;
                last = NULL;
            }
        }
        Node* getElement(int k) {
            // get k th smallest element in tree
            // k = [1..size]
            if (k < 1 || k > size()) {
                return NULL;
            }
            return getElement(root, k);
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
        cout << node->key << " ";
    }
    cout << endl;
    for (Node* node = avl.end(); node != NULL; node = node->prev){
        cout << node->key << " ";
    }
    cout << endl;

    cout << "Find 25: " << (avl.find(25) != NULL) << endl;
    cout << "Find 50: " << (avl.find(50) != NULL) << endl;
    cout << "Find 35: " << (avl.find(35) != NULL) << endl;

    AVL avl2;
    avl2.insert(9);
    avl2.insert(5);
    avl2.insert(10);
    avl2.insert(0);
    avl2.insert(6);
    avl2.insert(11);
    avl2.insert(-1);
    avl2.insert(1);
    avl2.insert(2);

    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    avl2.preOrder();
    cout << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;
    cout << avl2.begin()->key << " " << avl2.end()->key << endl;

    avl2.remove(10);
    cout << "remove 10: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    avl2.preOrder();
    cout << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(10);

    avl2.preOrder();
    cout << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(11);
    cout << "remove 11: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(6);
    cout << "remove 6: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(9);
    cout << "remove 9: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(0);
    cout << "remove 0: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(-1);
    cout << "remove -1: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.remove(2);
    cout << "remove 2: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.preOrder();
    cout << endl;
    avl2.remove(1);
    cout << "remove 1: (" << avl2.size() << ") " << avl2.begin()->key << " " << avl2.end()->key << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    avl2.preOrder();
    cout << endl;
    avl2.remove(5);
    cout << "remove 5: (" << avl2.size() << ") " << endl;
    for (Node* node = avl2.begin(); node != NULL; node = node->next){
        cout << node->key << " ";
    }
    cout << endl;

    return 0;
}

