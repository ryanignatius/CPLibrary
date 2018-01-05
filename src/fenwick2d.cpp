#include <bits/stdc++.h>

using namespace std;

typedef long long dataType;

class Fenwick2D {
	private:
		const static int MAXN = 105;
		const static int MAXM = 105;
		int N, M;
		dataType B1[MAXN][MAXM], B2[MAXN][MAXM], B3[MAXN][MAXM], B4[MAXN][MAXM];

		int LSOne(int S){
			return (S & (-S));
		}
		void build(int n, int m){
			N = n+10;
            M = m+10;
			memset(B1, 0, sizeof B1);
			memset(B2, 0, sizeof B2);
			memset(B3, 0, sizeof B3);
			memset(B4, 0, sizeof B4);
		}
		dataType query1(int d, int e){
			dataType sum = 0;
			for (int b = d; b; b -= LSOne(b)){
                for (int c = e; c; c -= LSOne(c)){
                    sum += B1[b][c];
                }
            }
			return sum;
		}
		dataType query2(int d, int e){
			dataType sum = 0;
			for (int b = d; b; b -= LSOne(b)){
                for (int c = e; c; c -= LSOne(c)){
                    sum += B2[b][c];
                }
            }
			return sum;
		}
		dataType query3(int d, int e){
			dataType sum = 0;
			for (int b = d; b; b -= LSOne(b)){
                for (int c = e; c; c -= LSOne(c)){
                    sum += B3[b][c];
                }
            }
			return sum;
		}
		dataType query4(int d, int e){
			dataType sum = 0;
			for (int b = d; b; b -= LSOne(b)){
                for (int c = e; c; c -= LSOne(c)){
                    sum += B4[b][c];
                }
            }
			return sum;
		}
		dataType query(int b, int c){
			return query1(b, c) * b * c - query2(b, c) * b - query3(b, c) * c + query4(b, c);
		}
		void update1(int kk, int hh, dataType v){
			for (int k = kk; k <= N; k += LSOne(k)){
                for (int h = hh; h <= M; h += LSOne(h)){
                    B1[k][h] += v;
                }
            }
		}
		void update2(int kk, int hh, dataType v){
			for (int k = kk; k <= N; k += LSOne(k)){
                for (int h = hh; h <= M; h += LSOne(h)){
                    B2[k][h] += v;
                }
            }
		}
		void update3(int kk, int hh, dataType v){
			for (int k = kk; k <= N; k += LSOne(k)){
                for (int h = hh; h <= M; h += LSOne(h)){
                    B3[k][h] += v;
                }
            }
		}
		void update4(int kk, int hh, dataType v){
			for (int k = kk; k <= N; k += LSOne(k)){
                for (int h = hh; h <= M; h += LSOne(h)){
                    B4[k][h] += v;
                }
            }
		}

	public:
		Fenwick2D(int n, int m){
			build(n, m);
		}
		dataType queryRange(int i, int j, int a, int b){
			return query(a, b) - query(a, j - 1) - query(i - 1, b) + query(i - 1, j - 1);
		}
		void updateRange(int i, int j, int a, int b, dataType v){
			update1(i, j, v);
			update1(i, b + 1, -v);
			update1(a + 1, j, -v);
			update1(a + 1, b + 1, v);
			update2(i, j, v * (j - 1));
			update2(i, b + 1, -v * b);
			update2(a + 1, j, -v * (j - 1));
			update2(a + 1, b + 1, v * b);
			update3(i, j, v * (i - 1));
			update3(i, b + 1, -v * (i - 1));
			update3(a + 1, j, -v * a);
			update3(a + 1, b + 1, v * a);
			update4(i, j, v * (i - 1) * (j - 1));
			update4(i, b + 1, -v * (i - 1) * b);
			update4(a + 1, j, -v * a * (j - 1));
			update4(a + 1, b + 1, v * a * b);
		}
};

int main(){
	Fenwick2D fen(3, 3);
	fen.updateRange(1,1,2,2,1);
	cout << fen.queryRange(1,1,3,3) << endl;
	cout << fen.queryRange(1,1,1,3) << endl;
	cout << fen.queryRange(2,1,3,1) << endl;
	fen.updateRange(2,2,3,3,3);
	cout << fen.queryRange(1,1,3,3) << endl;
    cout << endl;

    Fenwick2D fen2(1, 5);
    fen2.updateRange(1,1,1,5,1);
    fen2.updateRange(1,2,1,5,1);
    fen2.updateRange(1,3,1,5,1);
    fen2.updateRange(1,4,1,5,1);
    fen2.updateRange(1,5,1,5,1);
	cout << fen2.queryRange(1,1,1,5) << endl;
    cout << endl;

    Fenwick2D fen3(5, 5);
    fen3.updateRange(2,2,4,4,4);
    cout << fen3.queryRange(1,1,3,3) << endl;
    fen3.updateRange(5,5,5,5,3);
    cout << fen3.queryRange(1,1,1,2) << endl;
    cout << fen3.queryRange(2,2,5,3) << endl;
	return 0;
}
