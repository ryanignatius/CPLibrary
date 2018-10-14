#include <bits/stdc++.h>

using namespace std;

typedef long long dataType;

class Fenwick {
    private:
        const static int MAXN = 105000;
        int N;
        dataType B1[MAXN], B2[MAXN];
        
        int LSOne(int S){
            return (S & (-S));
        }
        void build(int n){
            N = n+10;
            memset(B1, 0, sizeof B1);
            memset(B2, 0, sizeof B2);
        }
        void build(dataType *A, int n){
            build(n);
            for (int i=0; i<n; i++){
                updateRange(i+1, i+1, A[i]);
            }
        }
        dataType query1(int b){
            dataType sum = 0;
            for (; b; b -= LSOne(b)) sum += B1[b];
            return sum;
        }
        dataType query2(int b){
            dataType sum = 0;
            for (; b; b -= LSOne(b)) sum += B2[b];
            return sum;
        }
        dataType query(int b){
            return query1(b) * b - query2(b);
        }
        void update1(int k, dataType v){
            for (; k <= N; k += LSOne(k)) B1[k] += v;
        }
        void update2(int k, dataType v){
            for (; k <= N; k += LSOne(k)) B2[k] += v;
        }

    public:
        Fenwick(int n){
            build(n);
        }
        Fenwick(dataType *A, int n){
            build(A, n);
        }
        dataType queryRange(int i, int j){
            return query(j) - query(i - 1);
        }
        void updateRange(int i, int j, dataType v){
            update1(i, v);
            update1(j + 1, -v);
            update2(i, v * (i - 1));
            update2(j + 1, -v * j);
        }
};

int main(){
    dataType arr[] = {1,2,3,4,5,6,7,8,9,10};
    Fenwick fen(arr, 10);
    cout << fen.queryRange(2,9) << endl;
    fen.updateRange(1,5,1);
    fen.updateRange(6,10,2);
    cout << fen.queryRange(2,9) << endl;
    return 0;
}
