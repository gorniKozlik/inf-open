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
    vector<pair<int, int>> g(2*n+1);
    int f = 0;
    int cur = 0;
    for (int i = 0; i < 2*n-1; ++i) {
        if (s[i].second == 0) {
            cur++;
        }else {
            cur--;
            f++;
        }
        g[i] = {min(f, n - f - cur), cur};
    }
    while (q--) {
        int k;
        cin >> k;
        int best = n;
        for (int i = 0; i < 2*n-1; ++i) {
            int can = g[i].first;
            int len = g[i].second;
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