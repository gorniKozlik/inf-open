#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx")

#define int long long
#define all(a) a.begin(), a.end()

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    sort(all(v));
    int mnr = v[0].second;
    int cur = 1;
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (v[i].first > mnr) {
            best = max(best, cur);
            cur = 1;
            mnr = v[i].second;
        }else {
            mnr = min(v[i].second, mnr);
        }
    }
    best = max(best, cur);
    while (q--) {
        int k;
        cin >> k;
        cout << max(0ll, k-best) << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
        cout << '\n';
    }
}