#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

class Centroid {
    private:
        const static int MAXN = 200100;
        int N;
        vector<ii> adj[MAXN];
        int parent[MAXN];
        int blocked[MAXN];
        ll subtreeSum[MAXN];
        queue<int> q;

        void calcSum(int cur, int par) {
            parent[cur] = par;
            subtreeSum[cur] = 1;
            for (int i=0; i<adj[cur].size(); i++) {
                ii v = adj[cur][i];
                if (v.first != par && !blocked[v.first]) {
                    calcSum(v.first, cur);
                    subtreeSum[cur] += subtreeSum[v.first];
                }
            }
        }

        // adjust
        int val(char a) {
            int x = (a-'a');
            return 1<<x;
        }
        void dfsmemo(int cur, int cen, int par, int num) {
            children[num].push_back(cur);
            memo[cur] = memo[par] ^ val(s[cur]);
            cnt[memo[cur]]++;
            for (int i=0; i<adj[cur].size(); i++) {
                ii v = adj[cur][i];
                if (v.first != par && !blocked[v.first]) {
                    dfsmemo(v.first, cen, cur, num);
                }
            }
        }
        ll dfsans(int cur, int root, int par) {
            int temp = memo[cur] ^ memo[root];
            ll curans = 0;
            curans += cnt[temp];
            for (int j=0; j<20; j++) {
                curans += cnt[temp ^ (1<<j)];
            }
            for (int i=0; i<adj[cur].size(); i++) {
                ii v = adj[cur][i];
                if (v.first != par && !blocked[v.first]) {
                    curans += dfsans(v.first, root, cur);
                }
            }
//            cout << "dfs cur: " << cur << " root: " << root << " par: " << par << " = " << curans << endl; 
            ans[cur] += curans;
            return curans;
        }
        ll dfsans2(int cur, int root, int par) {
            int temp = memo[cur] ^ memo[root];
            ll curans = 0;
            if (__builtin_popcount(temp) <= 1) {
                curans += 1;
            }
            for (int i=0; i<adj[cur].size(); i++) {
                ii v = adj[cur][i];
                if (v.first != par && !blocked[v.first]) {
                    curans += dfsans2(v.first, root, cur);
                }
            }
            ans[cur] += curans;
            return curans;
        }

    public:
        // adjust
        ll ans[200200];
        ll memo[200200];
        ll cnt[(1<<20)+10];
        string s;
        vector<int> children[200200];
        int numChildren;

        Centroid(int n, vector<ii> *adjarr) {
            N = n;
            for (int i=0; i<N; i++){
                adj[i] = adjarr[i];
            }
            memset(parent, -1, sizeof parent);
            memset(subtreeSum, 0, sizeof subtreeSum);
            memset(blocked, 0, sizeof blocked);
            memset(ans, 0, sizeof ans);
            memset(memo, 0, sizeof memo);
            memset(cnt, 0, sizeof cnt);
        }
        
        // adjust
        ll solveTree(int root, int compSize) {
//          cout << "root: " << root << " compsize: " << compSize << endl;
            memo[root] = 0;
            numChildren = 0;
            for (int i=0; i<adj[root].size(); i++) {
                ii v = adj[root][i];
                if (!blocked[v.first]) {
                    children[numChildren].clear();
                    dfsmemo(v.first, root, root, numChildren);
                    numChildren++;
                }
            }
            memo[root] = val(s[root]);
            ll tempans = 0;
            ll tempans2 = 0;
            for (int comp=0; comp<numChildren; comp++) {
                for (int i=0; i<children[comp].size(); i++) {
                    int cur = children[comp][i];
                    cnt[memo[cur]]--;
                }
                if (children[comp].size() > 0) {
                    int cur = children[comp][0];
                    tempans += dfsans(cur, root, root);
                    tempans2 += dfsans2(cur, root, root);
                }
                for (int i=0; i<children[comp].size(); i++) {
                    int cur = children[comp][i];
                    cnt[memo[cur]]++;
                }
            }
            ans[root] += (tempans/2 + tempans2);
            for (int comp=0; comp<numChildren; comp++) {
                for (int i=0; i<children[comp].size(); i++) {
                    int cur = children[comp][i];
                    cnt[memo[cur]] = 0;
                }
            }
            return ans[root];
        }

        ll dfs(int cur) {
            calcSum(cur, cur);
            int centroid = cur;
            ll bestSize = subtreeSum[cur];
            int compSize = 0;
            q.push(cur);
            while (!q.empty()) {
                int c = q.front();
                q.pop();
                compSize++;
                ll size = subtreeSum[cur] - subtreeSum[c];
                for (int i=0; i<adj[c].size(); i++){
                    ii v = adj[c][i];
                    if (v.first != parent[c] && !blocked[v.first]) {
                        size = max(size, subtreeSum[v.first]);
                        q.push(v.first);
                    }
                }
                if (size < bestSize) {
                    centroid = c;
                    bestSize = size;
                }
            }

            //cout << "Centroid: " << (centroid+1) << endl;

            ll ways = solveTree(centroid, compSize);
            blocked[centroid] = 1;
            for (int i=0; i<adj[centroid].size(); i++) {
                ii v = adj[centroid][i];
                if (!blocked[v.first]) {
                    ways += dfs(v.first);
                }
            }
            return ways;
        }
};

Centroid *cen;
int n,a,b,c;
vector<ii> adj[200100];
string s;

int main(){
    // http://codeforces.com/contest/914/problem/E
    scanf("%d", &n);
    for (int i=1; i<n; i++){
        scanf("%d%d", &a, &b);
        a--;
        b--;
        adj[a].push_back(ii(b,0));
        adj[b].push_back(ii(a,0));
    }
    cin >> s;
    cen = new Centroid(n, adj);
    cen->s = s;
    cen->dfs(0);
    for (int i=0; i<n; i++) {
        //printf("%I64d ", cen->ans[i] + 1);
        printf("%lld ", cen->ans[i] + 1);
    }
    printf("\n");
    return 0;
}
