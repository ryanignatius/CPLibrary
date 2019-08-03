#include <bits/stdc++.h>

using namespace std;

typedef int dataType;

typedef pair<int, int> ii;
typedef pair<ii, ii> element;

class Mos {
    private:
        const static int MAXN = 105000;
        const static int SQRTN = 350;
        vector<element> queries;
        vector<dataType> ans;
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
        int getL(element el) {
            return el.second.first;
        }
        int getR(element el) {
            return el.first.second;
        }
        int getId(element el) {
            return el.second.second;
        }

        void build(dataType *Arr, int n){
            N = n;
            for (int i=0; i<N; i++){
                A[i] = Arr[i];
            }
            bsize = (int)(ceil(sqrt(N)));
        }

    public:
        Mos(dataType *Arr, int n){
            build(Arr, n);
        }

        void addQueries(int id, int l, int r) {
            int lb = getBucket(l);
            queries.push_back(element(ii(lb, r), ii(l, id)));
            ans.push_back(0);
        }

        void printAns() {
            // adjust
            for (int i=0; i<ans.size(); i++) {
                cout << ans[i] << "\n";
            }
        }

        void compute() {
            sort(queries.begin(), queries.end());
            // adjust
            int a = getL(queries[0]);
            int b = a;
            dataType temp = A[a];
            for (int i=0; i<queries.size(); i++) {
                int curL = getL(queries[i]);
                int curR = getR(queries[i]);
                if (curR < b) {
                    // reset
                    a = b = curL;
                    temp = A[a];
                }
                while (b < curR) {
                    b++;
                    temp += A[b];
                }
                while (a != curL) {
                    if (a < curL) {
                        temp -= A[a];
                        a++;
                    } else {
                        a--;
                        temp += A[a];
                    }
                }
                ans[getId(queries[i])] = temp;
            }
        }
};

int n,q,l,r,ans;
int arr[100100];
Mos *mos;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }
    mos = new Mos(arr, n);
    cin >> q;
    for (int i=0; i<q; i++) {
        cin >> l >> r;
        l--;
        r--;
        mos->addQueries(i, l, r);
    }
    mos->compute();
    mos->printAns();
    return 0;
}
