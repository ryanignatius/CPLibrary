#include <bits/stdc++.h>

using namespace std;

typedef long long arrayType;
typedef long long treeType;

class SegTree {
    private:
        const static int MAXN = 105000;
        const static int ROOT = 1;
        int N;
        treeType tree[4*MAXN];
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
        void updateFunction(int node, int start, int end, treeType val){
            tree[node] += (end - start + 1) * val;
        }
        treeType queryFunction(treeType t1, treeType t2){
            return t1 + t2;
        }
        void init(){
            memset(tree, 0, sizeof tree);
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
        void update(int node, int start, int end, int l, int r, treeType val){
            if(start > end || start > r || end < l) return;
            if(start >= l && end <= r){
                updateFunction(node, start, end, val);
                return;
            }
            update(left(node), start, mid(start, end), l, r, val);
            update(right(node), mid(start, end)+1, end, l, r, val);
            joinFunction(node);
        }
        treeType query(int node, int start, int end, int l, int r){
            if(start > end || start > r || end < l) return 0;
            if(start >= l && end <= r) return tree[node];
            treeType p1 = query(left(node), start, mid(start, end), l, r);
            treeType p2 = query(right(node), mid(start, end)+1, end, l, r);
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
        void update(int l, treeType val){
            update(ROOT, 0, N-1, l, l, val);
        }
        treeType query(int l, int r){
            return query(ROOT, 0, N-1, l, r);
        }
};

int main(){
    arrayType arr[] = {1,2,3,4,5,6,7,8,9,10};
    SegTree seg(10, arr);
    cout << seg.query(1,8) << endl;
    seg.update(5,5);
    seg.update(6,6);
    cout << seg.query(1,8) << endl;
    return 0;
}
