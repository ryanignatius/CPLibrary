#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class SAT {
    private:
        static const int MAXN = 5000;
        vi adj[MAXN];
        vi adj2[MAXN];
        vi x, y;
        int n;
        int component[MAXN];
        int marked[MAXN];
        int counter;
        stack<int> stak;
        
        void dfs(int u) {
            marked[u] = 1;
            int v;
            for (int i=0; i<adj[u].size(); i++) {
                v = adj[u][i];
                if (!marked[v]) {
                    dfs(v);
                }
            }
            stak.push(u);
        }
        void dfs2(int u) {
            marked[u] = 1;
            int v;
            for (int i=0; i<adj2[u].size(); i++) {
                v = adj2[u][i];
                if (!marked[v]) {
                    dfs2(v);
                }
            }
            component[u] = counter;
        }
    public:
        SAT(int N) {
            n = N;
        }
        int nott(int x) {
            int ret = x+n;
            ret %= (2*n);
            return ret;
        }
        void addEdge(int xx, int yy) {
            x.push_back(xx);
            y.push_back(yy);
            adj[nott(xx)].push_back(yy);
            adj[nott(yy)].push_back(xx);
            adj2[yy].push_back(nott(xx));
            adj2[xx].push_back(nott(yy));
        }
        bool isSat() {
            memset(marked, 0, sizeof marked);
            for (int i=0; i<x.size(); i++) {
                if (!marked[x[i]]) dfs(x[i]);
                if (!marked[y[i]]) dfs(y[i]);
                if (!marked[nott(x[i])]) dfs(nott(x[i]));
                if (!marked[nott(y[i])]) dfs(nott(y[i]));
            }
            memset(component, -1, sizeof component);
            memset(marked, 0, sizeof marked);
            counter = 0;
            int v;
            while (!stak.empty()) {
                v = stak.top();
                stak.pop();
                if (!marked[v]) {
                    counter++;
                    dfs2(v);
                }
            }
            for (int i=0; i<x.size(); i++) {
                if (component[x[i]] == component[nott(x[i])]) return false;
            }
            return true;
        }
};

SAT *sat;
int t;
int n,m;
int a,b;

int main() {
    n = 3;
    sat = new SAT(n);
    sat->addEdge(0, 1);
    sat->addEdge(sat->nott(0), sat->nott(1));
    sat->addEdge(1, 2);
    sat->addEdge(sat->nott(1), sat->nott(2));
    sat->addEdge(0, 2);
    sat->addEdge(sat->nott(0), sat->nott(2));
    if (sat->isSat()) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    n = 4;
    sat = new SAT(n);
    sat->addEdge(0, 1);
    sat->addEdge(sat->nott(0), sat->nott(1));
    sat->addEdge(2, 3);
    sat->addEdge(sat->nott(2), sat->nott(3));
    if (sat->isSat()) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
