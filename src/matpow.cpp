#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;

// matrix power
// usage : find pattern
// matrix X (fn+1, fn) = (fn+2, fn+1)
// O(n^3 log p)
const int maxn = 2; // matrix size
ll mm = 1e9+7; // modulo
struct Matrix{ll mat[maxn][maxn]; };

Matrix matMul(Matrix a, Matrix b){
    Matrix ans;
    int i,j,k;
    for (int i=0; i<maxn; i++){
        for (int j=0; j<maxn; j++){
            for (ans.mat[i][j] = k = 0; k<maxn; k++){
                ans.mat[i][j] += (a.mat[i][k]*b.mat[k][j]);
                if (ans.mat[i][j] >= mm) ans.mat[i][j] %= mm;
            }
        }
    }
    return ans;
}

Matrix matPow(Matrix base, ll p){
    Matrix ans;
    int i,j;
    for (int i=0; i<maxn; i++){
        for (int j=0; j<maxn; j++){
            ans.mat[i][j] = (i == j);
        }
    }
    while (p){
        if (p%2==1) ans = matMul(ans,base);
        base = matMul(base,base);
        p >>= 1;
    }
    return ans;
}

int main(){
    Matrix m1,m2;
    // adjust m1
    m1.mat[0][0] = 1;
    m1.mat[0][1] = 1;
    m1.mat[1][0] = 1;
    m1.mat[1][1] = 0;
    m2 = matPow(m1,3);
    cout << m1.mat[0][0] << " " << m1.mat[0][1] << " " << m1.mat[1][0] << " " << m1.mat[1][1] << endl;
    cout << m2.mat[0][0] << " " << m2.mat[0][1] << " " << m2.mat[1][0] << " " << m2.mat[1][1] << endl;
    return 0;
}
