#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class BiMatching {
    private:
        static const int MAXN = 222;
        vi owner, visited;
        vi adjList[2*MAXN];
        int n;

        int altPath(int left){
            if (visited[left]) return 0;
            visited[left] = 1;
            for (int j=0; j<adjList[left].size(); j++){
                int right = adjList[left][j];
                if (owner[right] == -1 || altPath(owner[right])){
                    owner[right] = left;
                    return 1;
                }
            }
            return 0;
        }
    public:
        BiMatching(int N) {
            n = N;
            owner.assign(n*2, -1);
        }
        void addEdge(int x, int y) {
            adjList[x].push_back(y);
        }
        int maxMatching() {
            int ret = 0;
            for (int i=0; i<n; i++) {
                visited.clear();
                visited.assign(n*2, 0);
                ret += altPath(i);
            }
            return ret;
        }
};

int t,n,ans;
int arr[222][222];
BiMatching *bm;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    for (int tc=1; tc<=t; tc++) {
        cin >> n;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                cin >> arr[i][j];
            }
        }
        ans = n*n;
        for (int i=-n; i<=n; i++) {
            bm = new BiMatching(n);
            for (int aa=0; aa<n; aa++) {
                for (int bb=0; bb<n; bb++) {
                    if (arr[aa][bb] == i) {
                        bm->addEdge(aa, bb+n);
                    }
                }
            }
            ans -= bm->maxMatching();
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
