#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << x / 2 << " ";
    }
}

int main() {
    int T = 1;
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}