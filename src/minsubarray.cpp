#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

class MinSubArray {
    private:
        static const int MAXN = 100100;
        int n;
        int arr[MAXN];
    public:
        MinSubArray(int *sarr, int N) {
            n = N;
            for (int i=0; i<n; i++) {
                arr[i] = sarr[i];
            }
        }
        vector<int> getMinSubArray(int k) {
            vector<int> result;
            deque<ii> window;
            for (int i=0; i<n; i++) {
                while (!window.empty() && window.back().first >= arr[i]) {
                    window.pop_back();
                }
                window.push_back(ii(arr[i], i));
                while (window.front().second <= i-k) {
                    window.pop_front();
                }
                if (i+1 >= k) {
                    result.push_back(window.front().first);
                }
            }
            return result;
        }
};

int main() {
    int n = 5;
    int arr[] = {5, 3, 2, 1, 4};
    cout << "array: " << endl;
    for (int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    MinSubArray m(arr, n);
    cout << "window 3:" << endl;
    vector<int> w3 = m.getMinSubArray(3);
    for (int i=0; i<w3.size(); i++) {
        cout << w3[i] << " ";
    }
    cout << endl;
    cout << "window 2:" << endl;
    vector<int> w2 = m.getMinSubArray(2);
    for (int i=0; i<w2.size(); i++) {
        cout << w2[i] << " ";
    }
    cout << endl;
    return 0;
}
