#include <bits/stdc++.h>

using namespace std;

typedef long long weightType;

typedef pair<int, int> ii;
typedef pair<int, weightType> adjType;
typedef pair<weightType, ii> edge;

const int MAXN = 1010;

class Prim {
private:
    int n, m;
    priority_queue<edge> pq;
    vector<adjType> adj[MAXN];
    bool vis[MAXN];

public:
    Prim(int N, int M) {
        n = N;
        m = M;
        for (int i=0; i<n; i++) {
            adj[i].clear();
        }
        memset(vis, 0, sizeof vis);
    }

    void addEdge(int from, int to, weightType weight) {
        adj[from].push_back(adjType(to, weight));
        adj[to].push_back(adjType(from, weight));
    }

    weightType mst(int root) {
        weightType ret = 0;
        int numedge = 0;
        adjType v;
        for (int i=0; i<adj[root].size(); i++) {
            v = adj[root][i];
            pq.push(edge(-v.second, ii(root, v.first)));
        }
        vis[root] = true;
        edge cur;
        int a,b;
        while (!pq.empty()) {
            cur = pq.top();
            pq.pop();
            a = cur.second.first;
            b = cur.second.second;
            if (vis[b]) continue;
            vis[b] = true;
            ret += (-cur.first);
            numedge++;
            for (int i=0; i<adj[b].size(); i++) {
                v = adj[b][i];
                pq.push(edge(-v.second, ii(b, v.first)));
            }
        }
        if (numedge != n-1) return -1;
        return ret;
    }
};

int main() {
    Prim prim(3, 4);
    prim.addEdge(0, 1, 40);
    prim.addEdge(0, 2, 60);
    prim.addEdge(1, 2, 20);
    prim.addEdge(2, 1, 10);
    cout << "minimal cost: " << prim.mst(0) << endl;
    return 0;
}
