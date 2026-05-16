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
    vector<pair<int, int>> s;
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
        s.push_back({v[i].first, 0});
        s.push_back({v[i].second, 1});
    }
    sort(all(s));
    vector<pair<int, int>> g(2*n-1);
    int f = 0;
    int cur = 0;
    int mx = 0;
    for (int i = 0; i < 2*n-1; ++i) {
        if (s[i].second == 0) {
            cur++;
        }else {
            cur--;
            f++;
        }
        mx = max(mx, cur);
        g[i] = {min(f, n - f - cur), cur};
    }
    vector<pair<int, int>> t;
    for (auto x : g) {
        t.push_back({2*x.first + x.second, x.second});
    }
    sort(all(t));
    t.push_back({1e9, 0});
    vector<int> uwu(2*n);
    for (int i = 0; i < 2*n; ++i) {
        uwu[i] = t[i].first;
    }
    vector<int> m(2*n);
    for (int i = 2*n-2; i >= 0; --i) {
        m[i] = max(m[i+1], t[i].second);
    }
    vector<int> y(2*n);
    y[0] = t[0].first + t[0].second;
    for (int i = 1; i < 2*n-1; ++i) {
        y[i] = max(y[i-1], t[i].first + t[i].second);
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) {
            cout << 0 << " ";
            continue;
        }
        int best = n;
        int j = lower_bound(all(uwu), k) - uwu.begin();
        best = min(best, (k - m[j]+1)/2);
        if (j >= 1) {
            best = min(best, k - y[j-1]/2);
        }
        cout << best << " ";
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