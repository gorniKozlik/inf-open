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
    vector<pair<int, int>>b;
    for (int i = 0; i < n; ++i) {
        b.push_back({a[i].l, i});
        b.push_back({a[i].r, i});
    }
    sort(b.begin(), b.end());
    vector<int>maxi(2 * n);
    vector<int>c(n);
    for (int i = 1; i <= 2 * n; ++i) {
        c[b[i - 1].second]++;
        if (c[b[i - 1].second] == 2) {
            maxi[i] = maxi[i - 1] - 1;
        }
        else {
            maxi[i] = maxi[i - 1] + 1;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        int ans = 0;
        for (int i = x; i <= 2 * n - x; ++i) {
            ans = max(ans, maxi[i]);
        }
        cout << max(0, (x - ans + 1) / 2) << ' ';
    }
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