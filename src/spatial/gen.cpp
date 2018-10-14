#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 1000;
    int r;
    int x,y;
    cout << n << endl;
    for (int i=0; i<n; i++) {
        x = (rand() % 201) - 100;
        y = (rand() % 201) - 100;
        cout << x << " " << y << endl;
    }
    return 0;
}
