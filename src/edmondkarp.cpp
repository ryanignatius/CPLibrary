#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vl;

class Edge {
    public:
        int to;
        ll cap;
        int rev;

        Edge(int too, ll capp, int revv) {
            to = too;
            cap = capp;
            rev = revv;
        }
};

// O(v e^2)
class EdmondKarp {
    private:
        static const int MAXV = 505;
        static const ll MAXX = 1e8 * 1e8;
        ll res[MAXV][MAXV];
        vector<Edge> adj[MAXV];
        ll f;
        int n,s,t;
        vii p;

        void augment(int v, ll minEdge){
            if (v == s){
                f = minEdge;
                return;
            } else if (p[v].first != -1){
                int u = p[v].first;
                int i = p[v].second;
                augment(p[v].first, min(minEdge, adj[u][i].cap));
                adj[u][i].cap -= f;
                adj[v][adj[u][i].rev].cap += f;
            }
        }
    public:
        EdmondKarp(int N) {
            n = N;
            memset(res, 0, sizeof res);
        }
        void addCap(int x, int y, ll val) {
            res[x][y] += val;
        }
        void buildEdge() {
            int a,b;
            for (int i=0; i<n; i++) {
                for (int j=i+1; j<n; j++) {
                    if (res[i][j] + res[j][i] > 0) {
                        a = adj[i].size();
                        b = adj[j].size();
                        Edge edge1(j, res[i][j], b);
                        adj[i].push_back(edge1);
                        Edge edge2(i, res[j][i], a);
                        adj[j].push_back(edge2);
                    }
                }
            }
        }
        ll getMaxFlow(int S, int T) {
            s = S;
            t = T;
            ll mi = n;
            ll mf = 0;
            while (1) {
                f = 0;
                vl dist(mi, MAXX);
                dist[s] = 0;
                queue<int> q;
                q.push(s);
                p.assign(mi, ii(-1, -1));
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    if (u == t) break;
                    for (int i=0; i<adj[u].size(); i++) {
                        int v = adj[u][i].to;
                        if (adj[u][i].cap > 0 && dist[v] == MAXX) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                            p[v] = ii(u, i);
                        }
                    }
                }
                augment(t, MAXX);
                if (f == 0) break;
                mf += f;
            }
            return mf;
        }
};

int n,m,tc;
int a,b,c;
EdmondKarp *ek;

int main() {
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        ek = new EdmondKarp(n+2);
        while (m--) {
            cin >> a >> b >> c;
            ek->addCap(a, b, c);
            ek->addCap(b, a, c);
        }
        ek->buildEdge();
        cout << ek->getMaxFlow(1, n) << endl;
    }
    return 0;
}

