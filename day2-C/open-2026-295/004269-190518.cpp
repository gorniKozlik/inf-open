#pragma GCC optimize("O3,unroll-loops")
#include <string>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

struct Line {
    int l;
    int r;
};

void Solve () {
    int n, q;
    cin >> n >> q;
    vector<Line>a(n);
    for (auto& [l, r] : a) {
        cin >> l >> r;
    }
    while (q--) {
        int x;
        cin >> x;
    }
    vector<pair<int, int>>b;
    for (int i = 0; i < n; ++i) {
        b.push_back({a[i].l, i});
        b.push_back({a[i].r, i});
    }
    sort(b.begin(), b.end());
    vector<int>c(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        c[b[i].second]++;
        if (c[b[i].second] == 2) {
            ans++;
        }
    }
    cout << ans;
}

signed main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        Solve();
    }
}