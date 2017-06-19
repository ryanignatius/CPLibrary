#include <bits/stdc++.h>

using namespace std;

// Maximum flow of minimum cost with potentials
// O(min(E^2*V*logV, E*logV*FLOW))

typedef long long dt; // datatype
typedef pair<dt,dt> pdt; // pair of datatype
const dt INF = 1e18; // infinite value
const int MAXV = 2500; // max vertex number

class edge {
	public:
		int to;
		int rev;
		dt f;
		dt cap;
		dt cost;
		edge(){}
		edge(int v, dt cp, dt cs, int rv){
			to = v;
			cap = cp;
			cost = cs;
			rev = rv;
			f = 0;
		}
};

class MCMF {
	public:
		vector<edge> graph[MAXV];
		dt dist[MAXV];
		int n;
		MCMF(int N){
			n = N;
			for (int i=0; i<N; i++){
				graph[i].clear();
			}
		}
		void addEdge(int from, int to, dt cap, dt cost){
			edge e1(to, cap, cost, graph[to].size());
			edge e2(from, 0, -cost, graph[from].size());
			graph[from].push_back(e1);
			graph[to].push_back(e2);
		}
		void bellmanFord(int s){
			for (int i=0; i<n; i++){
				dist[i] = INF;
			}
			dist[s] = 0;
			int inqueue[MAXV];
			memset(inqueue, 0, sizeof inqueue);
			int q[MAXV];
			memset(q, 0, sizeof q);
			int qt = 0;
			q[qt++] = s;
			for (int qh = 0; (qh - qt) % n != 0; qh++) {
				int u = q[qh % n];
				inqueue[u] = 0;
				for (int i = 0; i < graph[u].size(); i++) {
					edge e = graph[u][i];
					if (e.cap <= e.f) continue;
					int v = e.to;
					dt ndist = dist[u] + e.cost;
					if (dist[v] > ndist) {
						dist[v] = ndist;
						if (!inqueue[v]) {
						inqueue[v] = 1;
							q[qt++ % n] = v;
						}
					}
				}
			}
		}
		pdt minCostFlow(int s, int t, dt maxf, bool bellman = false){
			dt prio[MAXV];
			dt curflow[MAXV];
			memset(curflow, 0, sizeof curflow);
			int prevedge[MAXV];
			memset(prevedge, 0, sizeof prevedge);
			int prevnode[MAXV];
			memset(prevnode, 0, sizeof prevnode);
			if (bellman){
				// bellmanFord invocation can be skipped if edges costs are non-negative
				bellmanFord(s);
		    } else {
		    	memset(dist, 0, sizeof dist);
		    }
		    dt flow = 0;
		    dt flowCost = 0;
		    while (flow < maxf){
		    	priority_queue<pdt> q;
		    	q.push(pdt(0, -s));
		    	for (int i=0; i<n; i++){
		    		prio[i] = INF;
		    	}
		    	prio[s] = 0;
		    	int finished[MAXV];
		    	memset(finished, 0, sizeof finished);
		    	curflow[s] = INF;
		    	while (!finished[t] && !q.empty()) {
					pdt cur = q.top();
					q.pop();
        			dt u = -cur.second;
        			dt priou = -cur.first;
					if (priou != prio[u]) continue;
					finished[u] = 1;
					for (int i = 0; i < graph[u].size(); i++) {
						edge e = graph[u][i];
						if (e.f >= e.cap) continue;
						int v = e.to;
						dt nprio = prio[u] + e.cost + dist[u] - dist[v];
						if (prio[v] > nprio) {
							prio[v] = nprio;
							q.push(pdt(-nprio, -v));
							prevnode[v] = u;
							prevedge[v] = i;
							curflow[v] = min(curflow[u], e.cap - e.f);
						}
					}
				}
				if (prio[t] == INF) break;
				for (int i = 0; i < n; i++){
					if (finished[i]){
						dist[i] += prio[i] - prio[t];
					}
				}
				dt df = min(curflow[t], maxf - flow);
				flow += df;
				for (int v = t; v != s; v = prevnode[v]) {
					edge e = graph[prevnode[v]][prevedge[v]];
					graph[prevnode[v]][prevedge[v]].f += df;
					graph[v][e.rev].f -= df;
					flowCost += df * e.cost;
				}
		    }
		    return pdt(flow, flowCost);
		}
};


int main (){
	int n,k;
	int a[2500];
	int b[2500];
	int ss = 0;
	int s = 1;
	int t = 2;
	scanf("%d%d", &n, &k);
	MCMF mcmf(n+3);
	mcmf.addEdge(ss, s, k, 0);
	for (int i=0; i<n; i++){
		scanf("%d", &a[i]);
		mcmf.addEdge(s, i+3, 1, a[i]);
		if (i>0){
			mcmf.addEdge(i+2, i+3, k, 0);
		}
	}
	for (int i=0; i<n; i++){
		scanf("%d", &b[i]);
		mcmf.addEdge(i+3, t, 1, b[i]);
	}
	cout << mcmf.minCostFlow(ss, t, INF, true).second << endl;
	return 0;
}

