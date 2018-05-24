#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

// O(v^3 e)
// O(v e^2)
class EdmondKarp {
    private:
        static const int MAXV = 505;
        static const ll MAXX = 1e8 * 1e8;
        ll res[MAXV][MAXV];
        ll f;
        int n,s,t;
        vi p;

        void augment(int v, ll minEdge){
            if (v == s){
                f = minEdge;
                return;
            } else if (p[v] != -1){
                augment(p[v], min(minEdge, res[p[v]][v]));
                res[p[v]][v] -= f;
                res[v][p[v]] += f;
            }
        }
    public:
        EdmondKarp(int N, int S, int T) {
            n = N;
            s = S;
            t = T;
            memset(res, 0, sizeof res);
        }
        void addCap(int x, int y, ll val) {
            res[x][y] = val;
        }
        ll getMaxFlow() {
            ll mi = n;
            ll mf = 0;
            while (1) {
                f = 0;
                vl dist(mi, MAXX);
                dist[s] = 0;
                queue<int> q;
                q.push(s);
                p.assign(mi, -1);
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    if (u == t) break;
                    for (int v=0; v<mi; v++) {
                        if (res[u][v] > 0 && dist[v] == MAXX) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                            p[v] = u;
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
        ek = new EdmondKarp(n+2, 1, n);
        while (m--) {
            cin >> a >> b >> c;
            ek->addCap(a, b, c);
            ek->addCap(b, a, c);
        }
        cout << ek->getMaxFlow() << endl;
    }
    return 0;
}

