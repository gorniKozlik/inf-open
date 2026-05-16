#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include<vector>
#pragma GCC optimize("avx2")
#endif

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using i128 = __int128;
using ll = long long;
using ld = long double;

template<typename T>
using orderet_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T, typename V>
using table = gp_hash_table<T, V>;

const int inf = 2e9 + 7;
const ll INF = 4e18 + 7;
const int maxn = 2e5 + 7;
const int MOD = 998244353;

#define int ll

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        mp[l[i]]++;
        mp[r[i]]++;
    }
    int m = 0;
    for (auto &c: mp)c.second = m++;
    vector<vector<int> > v(m);
    for (int i = 0; i < n; ++i) {
        l[i] = mp[l[i]];
        r[i] = mp[r[i]];
        v[l[i]].push_back(r[i]);
        v[r[i]].push_back(l[i]);
    }
    vector<int> a(m), b(m), c(m);
    int cntL = 0, cntR = n, cntOpen = 0;
    for (int i = 0; i < m; ++i) {
        int cntEnd = 0, cntStart = 0;
        for (auto x: v[i]) {
            if (x < i) {
                cntOpen--;
                cntEnd++;
            } else {
                cntR--;
                cntStart++;
            }
        }
        a[i] = cntOpen + cntStart + cntEnd;
        b[i] = min(cntL, cntR);
        c[i] = max(min(cntL - b[i], cntStart), min(cntR - b[i], cntEnd));
        cntOpen += cntStart;
        cntL += cntEnd;
    }
    vector<pair<int, pair<int, int> > > d(m);
    for (int i = 0; i < m; ++i) d[i] = {a[i], {b[i], c[i]}};
    sort(d.rbegin(), d.rend());
    vector<int> res(n + 1, inf);
    vector<int> mxC(n + 1, -inf);
    for (int i = 0; i < m; ++i) {
        int curr = d[i].first;
        auto [db, dc] = d[i].second;
        for (int j = 0; j <= db; ++j) {
            res[curr] = min(res[curr], j);
            curr += 2;
        }
        mxC[d[i].first + 2 * db] = max(mxC[d[i].first + 2 * db], dc);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= mxC[i]; ++j) {
            res[i + j] = min(res[i + j], res[i] + j);
        }
    }
    for (int i = n - 1; i >= 0; --i) res[i] = min(res[i], res[i + 1]);
    while (q--) {
        int x;
        cin >> x;
        cout << res[x] << " ";
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
