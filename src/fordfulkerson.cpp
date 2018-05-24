#include <bits/stdc++.h>

using namespace std;

class FordFulkerson {
    private:
        static const int MAXN = 1010;
        static const int MAXX = 1e9;
        int n,s,t;
        int cap[MAXN][MAXN];
        bool vis[MAXN];
        
        int findPath(int u, int f) {
            if (u == t) return f;
            vis[u] = 1;
            for (int v=0; v<n; v++) {
                if (!vis[v] && cap[u][v] > 0) {
                    int df = findPath(v, min(f, cap[u][v]));
                    if (df > 0) {
                        cap[u][v] -= df;
                        cap[v][u] += df;
                        return df;
                    }
                }
            }
            return 0;
        }
    public:
        FordFulkerson(int N, int S, int T) {
            n = N;
            s = S;
            t = T;
            memset(cap, 0, sizeof cap);
        }
        void addCap(int x, int y, int val) {
            cap[x][y] += val;
        }
        int getMaxFlow() {
            for (int flow = 0;;) {
                memset(vis, 0, sizeof vis);
                int df = findPath(s, MAXX);
                if (df == 0) return flow;
                flow += df;
            }
        }
};

int n,m,tc;
int a,b,c;
FordFulkerson *ff;

int main() {
    cin >> tc;
    while (tc--) {
        cin >> n >> m;
        ff = new FordFulkerson(n+2, 1, n);
        while (m--) {
            cin >> a >> b >> c;
            ff->addCap(a, b, c);
            ff->addCap(b, a, c);
        }
        cout << ff->getMaxFlow() << endl;
    }
    return 0;
}

