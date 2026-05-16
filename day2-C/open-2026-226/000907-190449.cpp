
#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")
#define int int64_t
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

const int INF = 1e9;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto &[l, r] : a)
        cin >> l >> r;


    sort(all(a), [&](pair<int, int> fi, pair<int, int> se) {
        if (fi.first == se.first)
            return fi.second > se.second;
        return fi.first < se.first;
    });

    vector<int> mn(n + 1, INF);

    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> z;
        
        for (int j = i; j < n; j++) {
            z.push_back({a[j].first, 1});
            z.push_back({a[j].second, 2});

            sort(all(z));

            int cnt = 0;

            for (int zv = 0; zv < j - i + 1; zv++)
                if (z[zv].second == 2)
                    cnt++;
            
            mn[j - i + 1] = min(mn[j - i + 1], cnt);
        }
    }


    for (int i = n - 1; i >= 0; i--)
        mn[i] = min(mn[i + 1], mn[i]);

    while (q--) {
        int x; cin >> x;
        cout << mn[x] << ' ';
    }
}