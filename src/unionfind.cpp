#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {
    private:
        vi p, rank;
    public:
        UnionFind(int N) {
            rank.assign(N, 0);
            p.assign(N, 0);
            for (int i = 0; i < N; i++) {
                p[i] = i;
            }
        }
        int findSet(int i) {
            return (p[i] == i) ? i : (p[i] = findSet(p[i]));
        }
        bool isSameSet(int i, int j) {
            return findSet(i) == findSet(j);
        }
        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) { // if from different set
                int x = findSet(i);
                int y = findSet(j);
                if (rank[x] > rank[y]) {
                    p[y] = x; // rank keeps the tree short
                } else {
                    p[x] = y;
                    if (rank[x] == rank[y]) rank[y]++;
                }
            }
        }
};

int main(){
    UnionFind uf(10);
    for (int i=0; i<10; i++){
        cout << i << " " << uf.findSet(i) << endl;
    }
    for (int i=1; i<10; i+=2){
        uf.unionSet(0, i);
    }
    for (int i=0; i<10; i++){
        cout << i << " " << uf.findSet(i) << endl;
    }
    return 0;
}
