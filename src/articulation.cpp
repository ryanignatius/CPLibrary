#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

class Articulation {
    private:
        const static int MAXN = 100100;
        int N;
        vector<int> dfs_num, dfs_low, dfs_parent;
        int dfsNumberCounter, dfsRoot, rootChildren;
        vector<int> adjList[MAXN];

        void articulationPointAndBridge(int u) {
            dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
            for (int j=0; j<adjList[u].size(); j++) {
                int v = adjList[u][j];
                if (dfs_num[v] == -1) {// a tree edge
                    dfs_parent[v] = u; // parent of this children is me
                    if (u == dfsRoot) {// special case
                        rootChildren++; // count children of root
                    }
                    articulationPointAndBridge(v);
                    if (dfs_low[v] >= dfs_num[u]) {// for articulation point
                        articulationPoint[u] = true; // store this information first
                    }
                    if (dfs_low[v] > dfs_num[u]) {// for bridge
                        articulationBridge[ii(u,v)] = true;
                        articulationBridge[ii(v,u)] = true;
                    }
                    dfs_low[u] = min(dfs_low[u], dfs_low[v]);
                } else if (v != dfs_parent[u]) {// a back edge and not direct cycle
                    dfs_low[u] = min(dfs_low[u], dfs_num[v]); // update dfs_low[u]
                }
            }
        }

    public:
        vector<bool> articulationPoint; // true if articulation point
        map<ii, bool> articulationBridge; // true if articulation bridge

        Articulation(int n, vector<int> *adj) {
            N = n;
            dfsNumberCounter = 0;
            dfs_num.assign(n+1, -1);
            dfs_low.assign(n+1, 0);
            dfs_parent.assign(n+1, -1);
            articulationPoint.assign(n+1, false);
            articulationBridge.clear();
            for (int i=0; i<N; i++){
                adjList[i] = adj[i];
            }
            for (int i=0; i<N; i++){
                if (dfs_num[i] == -1){
                    dfs_parent[i] = i;
                    dfsRoot = i;
                    rootChildren = 0;
                    articulationPointAndBridge(i);
                    articulationPoint[dfsRoot] = (rootChildren > 1); // special case
                }
            }
        }
};

int main(){
    vector<int> adj[100];
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(5);
    Articulation art(6, adj);
    for (int i=0; i<6; i++){
        cout << i << ": " << art.articulationPoint[i] << endl;
    }
    for (int i=0; i<6; i++){
        for (int j=0; j<adj[i].size(); j++){
            cout << i << "-" << adj[i][j] << ": " << art.articulationBridge[ii(i, adj[i][j])] << endl;
        }
    }
    return 0;
}
