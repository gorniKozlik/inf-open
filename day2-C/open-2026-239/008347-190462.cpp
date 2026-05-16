//#define _GLIBCXX_DEBUG
#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll mod = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n;i ++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> ans(n + 1);
    while (q--) {
        int k;
        cin >> k;
        if (n % 2 == 1) {
            cout << k / 2 << "\n";
        }
        else {
            exit(1);
            if (k == n) cout << n / 2;
            else cout << k / 2 << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << "\n";
    }
}