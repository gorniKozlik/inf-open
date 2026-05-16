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
    bool flag = 0;
    vector<pair<int, int>> g;
    for (int i = 1; i < n; ++i) {
        if (v[i].first > mnr) {
            if (flag) {
                g.push_back({g.back().second+1, i-1});
            }else {
                g.push_back({0, i-1});
                flag = 1;
            }
            cur = 1;
            mnr = v[i].second;
        }else {
            mnr = min(v[i].second, mnr);
        }
    }
    if (flag) {
        g.push_back({g.back().second+1, n-1});
    }else {
        g.push_back({0, n-1});
        flag = 1;
    }
    while (q--) {
        int k;
        cin >> k;
        int best = n;
        for (int i = 0; i < (int) g.size(); ++i) {
            int can = min(g[i].first, (n-g[i].second - 1));
            int len = g[i].second - g[i].first + 1;
            if (k <= len) {
                best = 0;
                break;
            }else {
                int ans = 0;
                if (k <= 2*can+len) {
                    ans += (k-len+1)/2;
                }else {
                    ans += can;
                    ans += (k - 2*can - len);
                }
                best = min(best, ans);
            }
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