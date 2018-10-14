#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;

class MathFunction {
    private:
        long long sieve_size;
        bitset<5000010> bs;
        vector<int> primes;

    public:
        bool isPrime(long long N) {
            if (N % 2 == 0) {
                if (N == 2) return true;
                return false;
            }
            if (N/2 < sieve_size) return bs[N/2];
            for (int i = 0; i < (int)primes.size(); i++)
                if (N % primes[i] == 0) return false;
            return true;
        }

        void sieve(long long upperbound) {
            sieve_size = (upperbound / 2) + (upperbound % 2);
            bs.set();
            bs[0] = 0;
            primes.clear();
            primes.push_back(2);
            long long step;
            for (long long i = 1; i < sieve_size; i++) {
                if (bs[i]) {
                    step = (i * 2 + 1);
                    for (long long j = step * i + i; j < sieve_size; j += step) {
                        bs[j] = 0;
                    }
                    primes.push_back((int) step);
                }
            }
        }
//};
        vector<int> primeFactors(long long N){
            vector<int> factors;
            long long idx = 0, pf = primes[idx];
            while(N!=1 && (pf * pf <= N)){
                while(N % pf == 0){
                    N /= pf;
                    factors.push_back(pf);
                }
                pf = primes[++idx];
            }
            if(N!=1) factors.push_back(N);
            return factors;
        }
//};
        long long fastExp(long long base, long long p){
            if(p==0) return 1;
            else if(p==1) return base;
            else {
                long long res = fastExp(base, p/2);
                res *= res;
                if (p % 2 == 1) res *= base;
                return res;
            }
        }
        
        long long fastExp(long long base, long long p, long long md){
            if (p == 0) return 1;
            else if (p == 1) return base;
            else {
                long long res = fastExp(base, p/2, md);
                res *= res;
                res %= md;
                if (p % 2 == 1) {
                    res *= base;
                    res %= md;
                }
                return res;
            }
        }

        // return a % b (positive value)
        ll mod(ll a, ll b) {
          return ((a%b)+b)%b;
        }

        // returns d = gcd(a,b); finds x,y such that d = ax + by
        ll extended_euclid(ll a, ll b, ll &x, ll &y) {  
          ll xx = y = 0;
          ll yy = x = 1;
          while (b) {
            ll q = a/b;
            ll t = b; b = a%b; a = t;
            t = xx; xx = x-q*xx; x = t;
            t = yy; yy = y-q*yy; y = t;
          }
          return a;
        }

        // Chinese remainder theorem (special case): find z such that
        // z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
        // Return (z,M).  On failure, M = -1.
        pll chinese_remainder_theorem(ll x, ll a, ll y, ll b) {
          ll ss, tt;
          ll d = extended_euclid(x, y, ss, tt);
          if (a%d != b%d) return make_pair(0, -1);
          return make_pair(mod(ss*b*x+tt*a*y,x*y)/d, x*y/d);
        }

        // Chinese remainder theorem: find z such that
        // z % x[i] = a[i] for all i.  Note that the solution is
        // unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
        // failure, M = -1.  Note that we do not require the a[i]'s
        // to be relatively prime.
        pll chinese_remainder_theorem(const vl &x, const vl &a) {
          pll ret = make_pair(a[0], x[0]);
          for (int i = 1; i < x.size(); i++) {
            ret = chinese_remainder_theorem(ret.second, ret.first, x[i], a[i]);
            if (ret.second == -1) break;
          }
          return ret;
        }
        
        ll gcd(ll a, ll b) {
            ll tmp;
            while (b){
                a %= b;
                tmp = a;
                a = b;
                b = tmp;
            }
            return a;
        }

        // computes lcm(a,b)
        ll lcm(ll a, ll b) {
          return a/gcd(a,b)*b;
        }
};

int main(){
    MathFunction fm;
    fm.sieve(25);
    for (int i=1; i<=20; i++){
        cout << i << ": " << fm.isPrime(i) << endl;
    }
    cout << fm.fastExp(2, 20) << endl;
    vector<int> pf = fm.primeFactors(100);
    for (int i=0; i<pf.size(); i++){
        if (i == 0) cout << "100 = ";
        else cout << " x ";
        cout << pf[i];
    }
    cout << endl;
    return 0;
}

