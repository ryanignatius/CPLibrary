#include <bits/stdc++.h>

using namespace std;

typedef long long weightType;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<weightType, ii> edge;

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
            if (!isSameSet(i, j)) {
                int x = findSet(i);
                int y = findSet(j);
                if (rank[x] > rank[y]) {
                    p[y] = x;
                } else {
                    p[x] = y;
                    if (rank[x] == rank[y]) rank[y]++;
                }
            }
        }
};

class Kruskal {
private:
    UnionFind *uf;
    int n, m;
    priority_queue<edge> pq;

public:
    Kruskal(int N, int M) {
        n = N;
        m = M;
        uf = new UnionFind(n);
    }

    void addEdge(int from, int to, weightType weight) {
        pq.push(edge(-weight, ii(from, to)));
    }

    weightType mst() {
        weightType ret = 0;
        int numedge = 0;
        edge cur;
        int a;
        int b;
        while (!pq.empty()) {
            cur = pq.top();
            pq.pop();
            a = cur.second.first;
            b = cur.second.second;
            if (!uf->isSameSet(a, b)) {
                uf->unionSet(a, b);
                ret += (-cur.first);
                numedge++;
            }
        }
        if (numedge != n-1) return -1;
        return ret;
    }
};

int main() {
    Kruskal kruskal(3, 4);
    kruskal.addEdge(0, 1, 40);
    kruskal.addEdge(0, 2, 60);
    kruskal.addEdge(1, 2, 20);
    kruskal.addEdge(2, 1, 10);
    cout << "minimal cost: " << kruskal.mst() << endl;
    return 0;
}
