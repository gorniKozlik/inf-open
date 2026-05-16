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
    while (q--) {
        int x;
        cin >> x;
        int maxi = 0;
        for (int i = 0; i <= 2 * n; ++i) {
            int ans = 0;
            vector<int>c(n);
            for (int j = 0; j < i; ++j) {
                c[b[j].second]++;
            }
            for (int j = 0; j < n; ++j) {
                if (c[j] == 1) {
                    ans++;
                }
            }
            maxi = max(maxi, ans);
        }
        cout << max(0, (x - maxi + 1) / 2) << ' ';
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