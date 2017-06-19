#include <bits/stdc++.h>

using namespace std;

class TarjanSCC {
	private:
		const static int MAXN = 100100;
		int N;
		vector<int> dfs_num, dfs_low, dfs_scc, visited;
		int dfsNumberCounter;
		vector<int> adjList[MAXN];

		void tarjanSCC(int u) {
			dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
			dfs_scc.push_back(u);
			visited[u] = 1; // stores u based on order of visitation
			for (int j=0; j<adjList[u].size(); j++) {
				int v = adjList[u][j];
				if (dfs_num[v] == -1) {// a tree edge
					tarjanSCC(v);
				}
				if (visited[v] == 1) {// condition for update
					dfs_low[u] = min(dfs_low[u], dfs_low[v]); // update dfs_low[u]
				}
			}
			if (dfs_low[u] == dfs_num[u]) { // if this is a root of SCC
				while (1) {
					int v = dfs_scc.back();
					dfs_scc.pop_back();
					visited[v] = 0;
					sccId[v] = numSCC;
					if (u == v) break;
				}
				numSCC++;
			}
		}

	public:
		vector<int> sccId;
		int numSCC;

		TarjanSCC(int n, vector<int> *adj) {
			N = n;
			dfs_num.assign(n+1, -1);
			dfs_low.assign(n+1, 0);
			visited.assign(n+1, 0);
			sccId.assign(n+1, -1);
			dfs_scc.clear();
			dfsNumberCounter = numSCC = 0;
			for (int i=0; i<N; i++){
				adjList[i] = adj[i];
			}
			for (int i=0; i<N; i++){
				if (dfs_num[i] == -1){
					tarjanSCC(i);
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
	TarjanSCC scc(6, adj);
	cout << scc.numSCC << endl;
	for (int i=0; i<6; i++){
		cout << i << ": " << scc.sccId[i] << endl;
	}
	return 0;
}

