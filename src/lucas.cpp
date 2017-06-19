#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;

// lucas theorem (nCr mod m, large n, large r, m prime)
class Lucas {
	private:
		const static int MAXN = 10100;
		int mx; // fac size
		ll mm; // modulo
		ll fac[MAXN];
		ll ifac[MAXN];
	public:
		// maxn, modulo
		Lucas(int n, ll m){
			mx = n;
			mm = m;
			prefac();
		}
		void prefac(){
		    fac[0] = 1;
		    ifac[0] = 1;
		    for (int i=1; i<=mx; i++){
			    fac[i] = (fac[i-1]*i)%mm;
				ifac[i] = fastExp(fac[i],mm-2);
		  	}
		}

		ll fastExp(ll aa, ll bb){
			if (bb == 0) return 1;
			if (bb == 1) return aa%mm;
			ll q = fastExp(aa,bb/2);
			q *= q;
			q %= mm;
			if (bb&1){
				q *= aa;
				q %= mm;
			}
			return q;
		}

		ll fastCombin(ll nn, ll cc){
			ll rr = nn-cc;
			ll ret = fac[nn];
			ret *= ifac[cc];
			ret %= mm;
			ret *= ifac[rr];
			ret %= mm;
			return ret;
		}

		ll lucas(ll nn, ll cc){
			if (nn < 0) return 0;
			if (cc < 0 || cc > nn) return 0;
			ll ret = 1;
			vl pb,py;
			ll temp = nn;
			while (temp > 0){
				pb.push_back(temp%mm);
				temp /= mm;
			}
			temp = cc;
			while (temp > 0){
				py.push_back(temp%mm);
				temp /= mm;
			}
			for (int i=0; i<py.size(); i++){
				if (py[i] > pb[i]) return 0;
				ret *= fastCombin(pb[i],py[i]);
				ret %= mm;
			}
			return ret;
		}
};

int main(){
	Lucas lucas(10000, 1e9+7);
	cout << lucas.lucas(10, 5) << endl;
	return 0;
}

