#include <bits/stdc++.h>

using namespace std;

typedef long long weightType;

const weightType INF = 1e18;
const int MAXN = 1010;

class DMST {
private:
    int n, m;
    int back[MAXN], label[MAXN], bio[MAXN];
    weightType cost[MAXN];
    vector<int> x, y;
    vector<weightType> w;

public:
    DMST(int N, int M) {
        n = N;
        m = M;
        x.clear();
        y.clear();
        w.clear();
    }

    void addEdge(int from, int to, weightType weight) {
        x.push_back(from);
        y.push_back(to);
        w.push_back(weight);
    }

    weightType dmst(int root) {
        int curroot = root;
        int curn = n;
        weightType ret = 0;
        while (1) {
            for (int i=0; i<curn; i++) {
                cost[i] = INF;
            }
            for (int i=0; i<m; i++) {
                if (x[i] == y[i]) continue;
                if (w[i] < cost[y[i]]) {
                    cost[y[i]] = w[i];
                    back[y[i]] = x[i];
                }
            }
            cost[curroot] = 0;
            for (int i=0; i<curn; i++) {
                if (cost[i] == INF) {
                    return -1;
                }
                ret += cost[i];
            }
            int comp = 0;
            int temp;
            memset(label, -1, sizeof label);
            memset(bio, -1, sizeof bio);
            for (int i=0; i<curn; i++) {
                temp = i;
                for (; temp != curroot && bio[temp] == -1; temp = back[temp]) {
                    bio[temp] = i;
                }
                if (temp != curroot && bio[temp] == i) {
                    for (; label[temp] == -1; temp = back[temp]) {
                        label[temp] = comp;
                    }
                    comp++;
                }
            }
            if (comp == 0) break;
            for (int i=0; i<curn; i++) {
                if (label[i] == -1) {
                    label[i] = comp;
                    comp++;
                }
            }
            int xx, yy;
            for (int i=0; i<m; i++) {
                xx = label[x[i]];
                yy = label[y[i]];
                if (xx != yy) {
                    w[i] -= cost[y[i]];
                }
                x[i] = xx;
                y[i] = yy;
            }
            curroot = label[curroot];
            curn = comp;
        }
        return ret;
    }
};

int main() {
    DMST dmst(3, 4);
    dmst.addEdge(0, 1, 40);
    dmst.addEdge(0, 2, 50);
    dmst.addEdge(1, 2, 20);
    dmst.addEdge(2, 1, 0);
    cout << "minimal cost: " << dmst.dmst(0) << endl;
    return 0;
}
