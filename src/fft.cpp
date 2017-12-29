#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cd;
typedef vector<cd> vcd;

using namespace std;

class FFT {
    private:
    public:
        vcd fft(const vcd &as) {
            int n = as.size();
            int k = 0;
            while ((1 << k) < n) k++;
            vector<int> rev(n);
            rev[0] = 0;
            int high1 = -1;
            for (int i = 1; i < n; i++) {
                if ((i & (i - 1)) == 0) {
                    high1++;
                }
                rev[i] = rev[i ^ (1 << high1)];
                rev[i] |= (1 << (k - high1 - 1));
            }

            vcd roots(n);
            for (int i = 0; i < n; i++) {
                double alpha = 2 * M_PI * i / n;
                roots[i] = cd(cos(alpha), sin(alpha));
            }

            vcd cur(n);
            for (int i = 0; i < n; i++) {
                cur[i] = as[rev[i]];
            }

            for (int len = 1; len < n; len <<= 1) {
                vcd ncur(n);
                int rstep = roots.size() / (len * 2);
                for (int pdest = 0; pdest < n;) {
                    int p1 = pdest;
                    for (int i = 0; i < len; i++) {
                        cd val = roots[i * rstep] * cur[p1 + len];
                        ncur[pdest] = cur[p1] + val;
                        ncur[pdest + len] = cur[p1] - val;
                        pdest++, p1++;
                    }
                    pdest += len;
                }
                cur.swap(ncur);
            }
            return cur;
        }

        vcd fft_rev(const vcd &as) {
            vcd res = fft(as);
            int sz = (int)as.size();
            for (int i = 0; i < (int)res.size(); i++) res[i] /= sz;
            reverse(res.begin() + 1, res.end());
            return res;
        }

        vcd fftMul(const vector<int> &v1, const vector<int> &v2) {
            int s = max((int)v1.size(), (int)v2.size());
            int n = 1;
            while (n < s){
                n <<= 1;
            }
            n <<= 1;

            vcd a(n);
            vcd b(n);
            for (int i=0; i<(int)v1.size(); i++) {
                a[i] = v1[i];
            }
            for (int i=(int)v1.size(); i<n; i++) {
                a[i] = 0;
            }
            for (int i=0; i<(int)v2.size(); i++) {
                b[i] = v2[i];
            }
            for (int i=(int)v2.size(); i<n; i++) {
                b[i] = 0;
            }

            vcd a_vals = fft(a);
            vcd b_vals = fft(b);
            vcd c_vals(a_vals.size());

            for (int i=0; i<(int)a_vals.size(); i++) {
                c_vals[i] = a_vals[i] * b_vals[i];
            }

            vcd c = fft_rev(c_vals);
            // for (int i = 0; i < c.size(); i++) printf("%.4lf %.4lf\n", c[i].real(), c[i].imag());
            return c;
        }
};

int main() {
    int n;
    scanf("%d", &n);
    vector<int> v1, v2;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v1.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v2.push_back(x);
    }
    FFT fft;
    vcd res = fft.fftMul(v1, v2);
    for (int i = 0; i < res.size(); i++)
        printf("%.4lf %.4lf\n", res[i].real(), res[i].imag());
    return 0;
}

