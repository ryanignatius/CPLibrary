#include <bits/stdc++.h>

using namespace std;

typedef long long dataType;

class SqrtDecompose {
    private:
        const static int MAXN = 105000;
        const static int SQRTN = 350;
        dataType memo[SQRTN];
        int bsize;
        int N;
        dataType A[MAXN];

        int getBucket(int a){
            return a/bsize;
        }
        int getStart(int a){
            return a*bsize;
        }
        int getEnd(int a){
            return ((a+1)*bsize)-1;
        }

        void build(dataType *Arr, int n){
            N = n;
            for (int i=0; i<N; i++){
                A[i] = Arr[i];
            }
            bsize = (int)(ceil(sqrt(N)));
            memset(memo, 0, sizeof memo);

            // adjust
            for (int i=0; i<N; i++){
                memo[getBucket(i)] += A[i];
            }
        }

    public:
        SqrtDecompose(dataType *Arr, int n){
            build(Arr, n);
        }

        // adjust
        dataType query(int l, int r){
            int lb = getBucket(l);
            int rb = getBucket(r);

            // adjust
            dataType e = 0;

            for (int i=lb; i<=rb; i++){
                int la = max(getStart(i),l);
                int ra = min(getEnd(i),r);
                if (la == getStart(i) && ra == getEnd(i)){
                    // full segment
                    // adjust
                    e += memo[i];
                } else {
                    // not full segment
                    if ((ra-la+1) <= bsize/2){
                        // iterate inside
                        for (int j=la; j<=ra; j++){
                            // adjust
                            e += A[j];
                        }
                    } else {
                        // add full bucket
                        // adjust
                        e += memo[i];
                        for (int j=getStart(i); j<la; j++){
                            // iterate outside
                            // adjust
                            e -= A[j];
                        }
                        for (int j=ra+1; j<=getEnd(i); j++){
                            // iterate outside
                            // adjust
                            e -= A[j];
                        }
                    }
                }
            }
            // adjust
            return e;
        }

};

int main(){
    dataType arr[] = {1,2,3,4,5,6,7,8,9,10};
    SqrtDecompose sq(arr, 10);
    cout << sq.query(1,8) << endl;
    cout << sq.query(3,6) << endl;
    cout << sq.query(9,9) << endl;
    return 0;
}
