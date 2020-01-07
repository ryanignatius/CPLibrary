#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

class Node {
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

class RowData {
public:
    int row, col, number, id;

    RowData() {}
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
    vector<RowData> rowData;
    vector<vector<RowData> > answers;

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
        while (h != header) {
            if (h->nodeCount < min_col->nodeCount) {
                min_col = h;
            }
            h = h->right;
        }
        return min_col;
    }

    void storeSolution() {
        vector<RowData> ans;
        vector<Node*>::iterator i;
        for (i = solutions.begin(); i != solutions.end(); i++) {
            ans.push_back(rowData[(*i)->rowID]);
        }
        answers.push_back(ans);
    }

public:
    DLX(int nCol, int bs = 0) {
        nodeList.clear();
        solutions.clear();
        numColumns = nCol;
        initHeader();
        curRow = 1;
        base = bs;
        rowData.clear();
        rowData.push_back(RowData());
        answers.clear();
    }

    void addRow(vector<int> cols, RowData data = RowData()) {
        data.id = curRow;
        rowData.push_back(data);
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
            storeSolution();
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

    vector<vector<RowData> > getSolutions() {
        return answers;
    }
};

class Sudoku {
private:
    const static int MAXN = 1050;
    int n;
    int arr[MAXN][MAXN];
    DLX *dlx;

    int getPositionConstraint(int row, int col) {
        return row * n + col;
    }

    int getHorizontalConstraint(int row, int number) {
        return (n * n) + (row * n + number - 1);
    }

    int getVerticalConstraint(int col, int number) {
        return (n * n * 2) + (col * n + number - 1);
    }

    int getBoxConstraint(int row, int col, int number) {
        int sn = sqrt(n);
        int rr = row / sn;
        int cc = col / sn;
        int box = rr * sn + cc;
        return (n * n * 3) + (box * n + number - 1);
    }

    void addDlxRow(int i, int j, int number) {
        RowData data;
        data.row = i + 1;
        data.col = j + 1;
        data.number = number;
        vector<int> cols;
        cols.push_back(getPositionConstraint(i, j));
        cols.push_back(getHorizontalConstraint(i, number));
        cols.push_back(getVerticalConstraint(j, number));
        cols.push_back(getBoxConstraint(i, j, number));
        dlx->addRow(cols, data);
    }

public:
    Sudoku(int N) {
        n = N;
        memset(arr, 0, sizeof arr);
        dlx = new DLX(n * n * 4);
    }

    void addNumber(int row, int col, int number) {
        arr[row - 1][col - 1] = number;
    }

    void printSudoku(string title) {
        cout << title << "\n";
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                cout << arr[i][j] << "  ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void printAllSolutions() {
        vector<vector<RowData> > sol = dlx->getSolutions();
        for (int i=0; i<sol.size(); i++) {
            Sudoku s(n);
            for (int j=0; j<sol[i].size(); j++) {
                s.addNumber(sol[i][j].row, sol[i][j].col, sol[i][j].number);
            }
            s.printSudoku("Solution #" + to_string(i + 1) + ":");
        }
    }

    void solve() {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (arr[i][j] == 0) {
                    for (int k=1; k<=n; k++) {
                        addDlxRow(i, j, k);
                    }
                } else {
                    addDlxRow(i, j, arr[i][j]);
                }
            }
        }
        dlx->search(0);
    }
};

class NQueen {
private:
    const static int MAXN = 1050;
    int n;
    int arr[MAXN];
    DLX *dlx;

    int getHorizontalConstraint(int i) {
        return i;
    }

    int getVerticalConstraint(int j) {
        return n + j;
    }

    int getDiagonal1Constraint(int i, int j) {
        int diag = j - i + n - 1;
        return (n * 2) + diag;
    }

    int getDiagonal2Constraint(int i, int j) {
        int diag = j + i;
        return (n * 4 - 1) + diag;
    }

    void addDlxRow(int i, int j) {
        RowData data;
        data.row = i + 1;
        data.col = j + 1;
        vector<int> cols;
        cols.push_back(getHorizontalConstraint(i));
        cols.push_back(getVerticalConstraint(j));
        cols.push_back(getDiagonal1Constraint(i, j));
        cols.push_back(getDiagonal2Constraint(i, j));
        dlx->addRow(cols, data);
    }

public:
    NQueen(int N) {
        n = N;
        dlx = new DLX(n * 6 - 2);
    }

    void addQueen(int row, int col) {
        if (row == 0 && col == 0) {
            return;
        }
        arr[row - 1] = col - 1;
    }

    void printBoard(string title) {
        cout << title << "\n";
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (arr[i] == j) {
                    cout << "Q";
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void printAllSolutions() {
        vector<vector<RowData> > sol = dlx->getSolutions();
        for (int i=0; i<sol.size(); i++) {
            NQueen s(n);
            for (int j=0; j<sol[i].size(); j++) {
                s.addQueen(sol[i][j].row, sol[i][j].col);
            }
            s.printBoard("Solution #" + to_string(i + 1) + ":");
        }
    }

    void solve() {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                addDlxRow(i, j);
            }
        }
        for (int i=n*2; i<n*6-2; i++) {
            vector<int> cols;
            cols.push_back(i);
            dlx->addRow(cols);
        }
        dlx->search(0);
    }
};

DLX *dlx;
Sudoku *sudoku;
NQueen *nqueen;

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
    vector<vector<RowData> > sol = dlx->getSolutions();
    for (int i=0; i<sol.size(); i++) {
        cout << "Solution #" << (i + 1) << ":";
        for (int j=0; j<sol[i].size(); j++) {
            cout << " " << sol[i][j].id;
        }
        cout << "\n";
    }

    /*
    Example 2: Sudoku 4x4
    ? 2 ? ?
    ? ? ? 1
    4 ? 3 2
    ? ? ? ?
    */

    sudoku = new Sudoku(4);
    sudoku->addNumber(1, 2, 2);
    sudoku->addNumber(2, 4, 1);
    sudoku->addNumber(3, 1, 4);
    sudoku->addNumber(3, 3, 3);
    sudoku->addNumber(3, 4, 2);
    sudoku->solve();
    sudoku->printSudoku("Original:");
    sudoku->printAllSolutions();

    /*
    Example 3: Sudoku 4x4
    ? ? 1 ?
    ? 4 ? ?
    ? ? 2 ?
    ? 3 ? ?
    */
    sudoku = new Sudoku(4);
    sudoku->addNumber(1, 3, 1);
    sudoku->addNumber(2, 2, 4);
    sudoku->addNumber(3, 3, 2);
    sudoku->addNumber(4, 2, 3);
    sudoku->solve();
    sudoku->printSudoku("Original:");
    sudoku->printAllSolutions();

    /*
    Example 4: NQueen 4x4
    */
    nqueen = new NQueen(4);
    nqueen->solve();
    nqueen->printAllSolutions();

    /*
    Example 5: NQueen 6x6
    */
    nqueen = new NQueen(6);
    nqueen->solve();
    nqueen->printAllSolutions();
    return 0;
}
