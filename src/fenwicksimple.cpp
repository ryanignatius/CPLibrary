#include <bits/stdc++.h>

using namespace std;

typedef long long dataType;

class Fenwick {
    private:
        const static int MAXN = 105000;
        int N;
        dataType B[MAXN];
        
        int LSOne(int S){
            return (S & (-S));
        }
        void build(int n){
            N = n+10;
            memset(B, 0, sizeof B);
        }
        void build(dataType *A, int n){
            build(n);
            for (int i=0; i<n; i++){
                update(i+1, A[i]);
            }
        }

    public:
        Fenwick(int n){
            build(n);
        }
        Fenwick(dataType *A, int n){
            build(A, n);
        }
        dataType query(int b){
            dataType sum = 0;
            for (; b; b -= LSOne(b)) sum += B[b];
            return sum;
        }
        dataType query(int i, int j){
            return query(j) - query(i - 1);
        }
        void update(int k, dataType v){
            for (; k <= N; k += LSOne(k)) B[k] += v;
        }
};

int main(){
    dataType arr[] = {1,2,3,4,5,6,7,8,9,10};
    Fenwick fen(arr, 10);
    cout << fen.query(2,9) << endl;
    fen.update(5,5);
    fen.update(6,6);
    cout << fen.query(2,9) << endl;
    return 0;
}
