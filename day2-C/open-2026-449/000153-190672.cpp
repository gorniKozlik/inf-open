#include <bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;
using ld = long double;

const int inf = 1e12;
const int mod = 998244353;


void go() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    while (q--) {
        int x;
        cin >> x;
        cout << x / 2 << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        go();
    }
}