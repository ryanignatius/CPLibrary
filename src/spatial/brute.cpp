#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int main() {
    int n;
    int x[1010], y[1010];
    int comparison = 0;
    vector<ii> v;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            comparison++;
            if (hypot(x[i]-x[j], y[i]-y[j]) <= 2.0f) {
                v.push_back(ii(i, j));
            }
        }
    }
    cout << comparison << endl;
    cout << v.size() << endl;
    for (int i=0; i<v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
    } 
    return 0;
}
