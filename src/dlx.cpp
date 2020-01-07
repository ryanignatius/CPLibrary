#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

class Node
{
public:
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Node *column;
    int rowID;
    int colID;
    int nodeCount;
};

// Exact Cover problem
// Dancing Link X
class DLX {
private:
    const static int MAX_ROW = 105000;
    const static int MAX_COL = 105000;
    Node *header;
    vector<Node*> nodeList;
    vector<Node*> solutions;
    int numRows;
    int numColumns;
    vector<int> rowList[MAX_ROW];
    vector<int> colList[MAX_COL];
    int curRow;
    int base;

    void initHeader() {
        header = new Node();
        for (int j = 0; j < numColumns; j++) {
            Node *node = new Node();
            node->column = node;
            node->up = node;
            node->down = node;
            node->rowID = 0;
            node->colID = j;
            node->nodeCount = 0;
            if (j > 0) {
                linkHorizontalNode(nodeList[rowList[0][rowList[0].size() - 1]], node);
            }
            rowList[0].push_back(nodeList.size());
            colList[j].push_back(nodeList.size());
            nodeList.push_back(node);
        }
        linkHorizontalNode(header, nodeList[rowList[0][0]]);
        linkHorizontalNode(nodeList[rowList[0][rowList[0].size() - 1]], header);
    }

    void linkHorizontalNode(Node* leftNode, Node* rightNode) {
        leftNode->right = rightNode;
        rightNode->left = leftNode;
    }

    void linkVerticalNode(Node* upNode, Node* downNode) {
        upNode->down = downNode;
        downNode->up = upNode;
    }

    void cover(Node *targetNode) {
        Node *row, *rightNode;
        Node *colNode = targetNode->column;
        colNode->left->right = colNode->right;
        colNode->right->left = colNode->left;
        for (row = colNode->down; row != colNode; row = row->down) {
            for (rightNode = row->right; rightNode != row; rightNode = rightNode->right) {
                rightNode->up->down = rightNode->down;
                rightNode->down->up = rightNode->up;
                rightNode->column->nodeCount--;
            }
        }
    }

    void uncover(Node *targetNode) {
        Node *rowNode, *leftNode;
        Node *colNode = targetNode->column;
        for (rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up) {
            for (leftNode = rowNode->left; leftNode != rowNode; leftNode = leftNode->left) {
                leftNode->up->down = leftNode;
                leftNode->down->up = leftNode;
                leftNode->column->nodeCount++;
            }
        }
        colNode->left->right = colNode;
        colNode->right->left = colNode;
    }

    Node *getMinColumn() {
        Node *h = header;
        Node *min_col = h->right;
        h = h->right->right;
        do {
            if (h->nodeCount < min_col->nodeCount) {
                min_col = h;
            }
            h = h->right;
        } while (h != header);
        return min_col;
    }

    void printSolutions() {
        cout << "Printing Solutions: ";
        vector<Node*>::iterator i;
        for (i = solutions.begin(); i != solutions.end(); i++) {
            cout << (*i)->rowID << " ";
        }
        cout << "\n";
    }

public:
    DLX(int nCol, int bs = 0) {
        nodeList.clear();
        solutions.clear();
        numColumns = nCol;
        initHeader();
        curRow = 1;
        base = bs;
    }

    void addRow(vector<int> cols) {
        sort(cols.begin(), cols.end());
        for (int j = 0; j < cols.size(); j++) {
            int col = cols[j] - base;
            Node *node = new Node();
            node->column = nodeList[col];
            linkVerticalNode(nodeList[colList[col][colList[col].size() - 1]], node);
            linkVerticalNode(node, node->column);
            node->rowID = curRow;
            node->colID = col;
            node->column->nodeCount++;
            if (j > 0) {
                linkHorizontalNode(nodeList[rowList[curRow][rowList[curRow].size() - 1]], node);
            }
            rowList[curRow].push_back(nodeList.size());
            colList[col].push_back(nodeList.size());
            nodeList.push_back(node);
        }
        linkHorizontalNode(nodeList[rowList[curRow][rowList[curRow].size() - 1]], nodeList[rowList[curRow][0]]);
        curRow++;
    }

    void search(int k) {
        Node *rowNode;
        Node *rightNode;
        Node *leftNode;
        Node *column;
        if (header->right == header) {
            printSolutions();
            return;
        }
        column = getMinColumn();
        cover(column);
        for (rowNode = column->down; rowNode != column; rowNode = rowNode->down) {
            solutions.push_back(rowNode);
            for (rightNode = rowNode->right; rightNode != rowNode; rightNode = rightNode->right) {
                cover(rightNode);
            }
            search(k+1);
            solutions.pop_back();
            column = rowNode->column;
            for (leftNode = rowNode->left; leftNode != rowNode; leftNode = leftNode->left) {
                uncover(leftNode);
            }
        }
        uncover(column);
    }
};

DLX *dlx;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /* 
     Example problem 
  
     X = {1,2,3,4,5,6,7} 
     set-1 = {1,4,7} 
     set-2 = {1,4} 
     set-3 = {4,5,7} 
     set-4 = {3,5,6} 
     set-5 = {2,3,6,7} 
     set-6 = {2,7} 
     set-7 = {1,4} 
  
     Solutions : {6 ,4, 2} and {6, 4, 7} 
    */
    dlx = new DLX(7, 1);
    vector<int> cols;
    cols.clear();
    cols.push_back(1);
    cols.push_back(4);
    cols.push_back(7);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(1);
    cols.push_back(4);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(4);
    cols.push_back(5);
    cols.push_back(7);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(3);
    cols.push_back(5);
    cols.push_back(6);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(2);
    cols.push_back(3);
    cols.push_back(6);
    cols.push_back(7);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(2);
    cols.push_back(7);
    dlx->addRow(cols);
    cols.clear();
    cols.push_back(1);
    cols.push_back(4);
    dlx->addRow(cols);

    dlx->search(0);
    return 0;
}
