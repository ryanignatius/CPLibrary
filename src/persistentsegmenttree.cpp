#include <bits/stdc++.h>

using namespace std;

typedef long long treeType;

class SegTree {
    private:
        const static int MAXN = 105000;
        const static int SIZE = 30*MAXN;

        int N;
        int NODES;
        int leftIdx[SIZE], rightIdx[SIZE];
        treeType tree[SIZE];
        treeType A[MAXN];

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
        void buildFunction(int p, treeType el){
            tree[p] = el;
        }
        void joinFunction(int p, treeType p1, treeType p2){
            tree[p] = p1 + p2;
        }
        treeType updateFunction(int p, treeType val){
            return val;
        }
        treeType queryFunction(treeType t1, treeType t2){
            return t1 + t2;
        }
        void init(){
            NODES = 0;
            tree[0] = 0;
            leftIdx[0] = 0;
            rightIdx[0] = 0;
        }
        // end adjust

        int newleaf(int value) {
            int p = ++NODES;
            leftIdx[p] = rightIdx[p] = 0;
            buildFunction(p, value);
            return p;
        }
        int newparent(int lef, int rig) {
            int p = ++NODES;
            leftIdx[p] = lef;
            rightIdx[p] = rig;
            joinFunction(p, tree[lef], tree[rig]);
            return p;
        }
        int build(int start, int end){
            if (start == end){
                return newleaf(A[start]);
            } else {
                return newparent(build(start, mid(start, end)), build(mid(start, end)+1, end));
            }
        }
        int update(int idx, treeType val, int p, int start, int end) {
            if (start == end) return newleaf(updateFunction(p, val));
            if (idx <= mid(start, end)) return newparent(update(idx, val, leftIdx[p], start, mid(start, end)), rightIdx[p]);
            else return newparent(leftIdx[p], update(idx, val, rightIdx[p], mid(start, end) + 1, end));
        }
        treeType query(int p, int start, int end, int l, int r) {
            if (start > end || start > r || end < l) return 0;
            if (start >= l && end <= r) return tree[p];
            treeType p1 = query(leftIdx[p], start, mid(start, end), l, r);
            treeType p2 = query(rightIdx[p], mid(start, end)+1, end, l, r);
            return queryFunction(p1, p2);
        }

    public:
        SegTree(int nn, treeType *Arr){
            N = nn;
            init();
            for (int i=0; i<nn; i++){
                A[i] = Arr[i];
            }
        }
        int build(){
            return build(0, N-1);
        }
        int update(int root, int idx, treeType val){
            return update(idx, val, root, 0, N-1);
        }
        treeType query(int root, int l, int r){
            return query(root, 0, N-1, l, r);
        }
};

SegTree *seg;

int main(){
    treeType arr[] = {0,1,2,3,4,5,6,7,8,9,10};
    seg = new SegTree(11, arr);
    int r1 = seg->build();
    cout << "Tes initial" << endl;
    cout << seg->query(r1,1,1) << endl;
    cout << seg->query(r1,1,2) << endl;
    cout << seg->query(r1,1,3) << endl;
    cout << seg->query(r1,1,4) << endl;
    cout << seg->query(r1,1,5) << endl;
    cout << seg->query(r1,1,6) << endl;
    cout << seg->query(r1,1,7) << endl;
    cout << seg->query(r1,1,8) << endl;
    cout << seg->query(r1,1,9) << endl;
    cout << seg->query(r1,1,10) << endl;
    int r2 = seg->update(r1, 5, 55);
    cout << "Tes use after update" << endl;
    cout << seg->query(r2,1,1) << endl;
    cout << seg->query(r2,1,2) << endl;
    cout << seg->query(r2,1,3) << endl;
    cout << seg->query(r2,1,4) << endl;
    cout << seg->query(r2,1,5) << endl;
    cout << seg->query(r2,1,6) << endl;
    cout << seg->query(r2,1,7) << endl;
    cout << seg->query(r2,1,8) << endl;
    cout << seg->query(r2,1,9) << endl;
    cout << seg->query(r2,1,10) << endl;
    cout << "Tes use before update" << endl;
    cout << seg->query(r1,1,10) << endl;
    cout << seg->query(r1,2,10) << endl;
    cout << seg->query(r1,3,10) << endl;
    cout << seg->query(r1,4,10) << endl;
    cout << seg->query(r1,5,10) << endl;
    cout << seg->query(r1,6,10) << endl;
    cout << seg->query(r1,7,10) << endl;
    cout << seg->query(r1,8,10) << endl;
    cout << seg->query(r1,9,10) << endl;
    cout << seg->query(r1,10,10) << endl;
    return 0;
}
