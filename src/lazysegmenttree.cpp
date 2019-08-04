#include <bits/stdc++.h>

using namespace std;

typedef long long arrayType;
typedef long long treeType;
typedef long long lazyType;

class SegTree {
    private:
        const static int MAXN = 105000;
        const static int ROOT = 1;
        int N;
        treeType tree[4*MAXN];
        lazyType lazy[4*MAXN];
        arrayType A[MAXN];

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
        }
        // end adjust

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
            if(start > end || start > r || end < l) return;
            if(start >= l && end <= r){
                updateFunction(node, start, end, val);
                return;
            }
            updateRange(left(node), start, mid(start, end), l, r, val);
            updateRange(right(node), mid(start, end)+1, end, l, r, val);
            joinFunction(node);
        }
        treeType queryRange(int node, int start, int end, int l, int r){
            if(start > end || start > r || end < l) return 0;
            if(lazy[node] != 0){
                lazyFunction(node, start, end);
            }
            if(start >= l && end <= r) return tree[node];
            treeType p1 = queryRange(left(node), start, mid(start, end), l, r);
            treeType p2 = queryRange(right(node), mid(start, end)+1, end, l, r);
            return queryFunction(p1, p2);
        }
    public:
        SegTree(int nn, arrayType *Arr){
            N = nn;
            init();
            for (int i=0; i<nn; i++){
                A[i] = Arr[i];
            }
            build(ROOT, 0, N-1);
        }
        void updateRange(int l, int r, treeType val){
            updateRange(ROOT, 0, N-1, l, r, val);
        }
        treeType queryRange(int l, int r){
            return queryRange(ROOT, 0, N-1, l, r);
        }
};

int main(){
    arrayType arr[] = {1,2,3,4,5,6,7,8,9,10};
    SegTree seg(10, arr);
    cout << seg.queryRange(1,8) << endl;
    seg.updateRange(0,4,1);
    seg.updateRange(5,9,2);
    cout << seg.queryRange(1,8) << endl;
    return 0;
}
