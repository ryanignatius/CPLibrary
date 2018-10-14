#include <bits/stdc++.h>

using namespace std;

typedef long long arrayType;
typedef long long treeType;
typedef long long lazyType;
typedef vector<int> vi;

class HLD {
    private:
        const static int MAXN = 105000;
        const static int ROOT = 1;
        int N;

        // Segment Tree
        treeType tree[4*MAXN];
        lazyType lazy[4*MAXN];
        arrayType A[MAXN];
        vi adj[MAXN];

        // HLD
        bool valuesOnVertices; // true - values on vertices, false - values on edges
        treeType parent[MAXN];
        treeType heavy[MAXN];
        treeType depth[MAXN];
        treeType pathRoot[MAXN];
        treeType pos[MAXN];

        int left(int node){
            return node*2;
        }
        int right(int node){
            return node*2+1;
        }
        int mid(int start, int end){
            return (start + end) / 2;
        }

        // adjust
        void buildFunction(int node, arrayType el){
            tree[node] = el;
        }
        void joinFunction(int node){
            tree[node] = tree[left(node)] + tree[right(node)];
        }
        void lazyFunction(int node, int start, int end){
            tree[node] += (end - start + 1) * lazy[node];
            if(start != end){
                lazy[left(node)] += lazy[node];
                lazy[right(node)] += lazy[node];
            }
            lazy[node] = 0;
        }
        void updateFunction(int node, int start, int end, treeType val){
            tree[node] += (end - start + 1) * val;
            if(start != end){
                lazy[left(node)] += val;
                lazy[right(node)] += val;
            }
        }
        treeType queryFunction(treeType t1, treeType t2){
            return t1 + t2;
        }
        void init(){
            memset(tree, 0, sizeof tree);
            memset(lazy, 0, sizeof lazy);
            memset(parent, 0, sizeof parent);
            memset(heavy, -1, sizeof heavy);
            memset(depth, 0, sizeof depth);
            memset(pathRoot, 0, sizeof pathRoot);
            memset(pos, 0, sizeof pos);

            parent[0] = -1;
            depth[0] = 0;
            dfs(0);
            
            for (int u=0, p=0; u<N; u++){
                if (parent[u] == -1 || heavy[parent[u]] != u){
                    for (int v=u; v != -1; v = heavy[v]){
                        pathRoot[v] = u;
                        pos[v] = p++;
                    }
                }
            }
        }
        // end adjust
        
        int dfs(int u){
            int size = 1;
            int maxSubtree = 0;
            for (int i=0; i<adj[u].size(); i++){
                int v = adj[u][i];
                if (v != parent[u]){
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    int subtree = dfs(v);
                    if (maxSubtree < subtree){
                        maxSubtree = subtree;
                        heavy[u] = v;
                    }
                    size += subtree;
                }
            }
            return size;
        }

        // Segment Tree
        void build(int node, int start, int end){
            if(start == end){
                buildFunction(node, A[start]);
            } else {
                build(left(node), start, mid(start, end));
                build(right(node), mid(start, end)+1, end);
                joinFunction(node);
            }
        }
        void updateRange(int node, int start, int end, int l, int r, treeType val){
            if(lazy[node] != 0){
                lazyFunction(node, start, end);
            }
            if(start > end or start > r or end < l) return;
            if(start >= l and end <= r){
                updateFunction(node, start, end, val);
                return;
            }
            updateRange(left(node), start, mid(start, end), l, r, val);
            updateRange(right(node), mid(start, end)+1, end, l, r, val);
            joinFunction(node);
        }
        treeType queryRange(int node, int start, int end, int l, int r){
            if(start > end or start > r or end < l) return 0;
            if(lazy[node] != 0){
                lazyFunction(node, start, end);
            }
            if(start >= l and end <= r) return tree[node];
            treeType p1 = queryRange(left(node), start, mid(start, end), l, r);
            treeType p2 = queryRange(right(node), mid(start, end)+1, end, l, r);
            return queryFunction(p1, p2);
        }
        void updateRange(int l, int r, treeType val){
            updateRange(ROOT, 0, N-1, l, r, val);
        }
        treeType queryRange(int l, int r){
            return queryRange(ROOT, 0, N-1, l, r);
        }
        
    public:
        HLD(int nn, arrayType *Arr, vi *ad, bool valueOnVertices){
            N = nn;
            valuesOnVertices = valueOnVertices;
            for (int i=0; i<nn; i++){
                for (int j=0; j<ad[i].size(); j++){
                    adj[i].push_back(ad[i][j]);
                }
            }
            init();
            memset(A, 0, sizeof A);
            build(ROOT, 0, N-1);
            for (int i=0; i<nn; i++){
                modify(i, i, Arr[i]);
            }
        }
        
        treeType query(int u, int v){
            treeType res = 0;
            for (; pathRoot[u] != pathRoot[v]; v = parent[pathRoot[v]]){
                if (depth[pathRoot[u]] > depth[pathRoot[v]]){
                    swap(u, v);
                }
                res += queryRange(pos[pathRoot[v]], pos[v]);
            }
            if (!valuesOnVertices && u == v) return res;
            res += queryRange(min(pos[u], pos[v]) + (valuesOnVertices ? 0 : 1), max(pos[u], pos[v]));
            return res;
        }
        
        void modify(int u, int v, treeType delta){
            for (; pathRoot[u] != pathRoot[v]; v = parent[pathRoot[v]]){
                if (depth[pathRoot[u]] > depth[pathRoot[v]]){
                    swap(u, v);
                }
                updateRange(pos[pathRoot[v]], pos[v], delta);
            }
            if (!valuesOnVertices && u == v) return;
            updateRange(min(pos[u], pos[v]) + (valuesOnVertices ? 0 : 1), max(pos[u], pos[v]), delta);
        }
};

int main(){
    return 0;
}
