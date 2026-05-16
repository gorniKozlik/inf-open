#include "bits/stdc++.h"
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
// using namespace __gnu_pbds;
// template<class T> 
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using ll = long long;
using ld = long double;

#define int long long

int f(pair<int, int>& a, pair<int, int>& b) {
    return (b.first - a.first + b.second - a.second) - (a.second - a.first) - (b.second - b.first);
}

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> a; // [-l, -r]
    set<pair<int, int>> b; // [r, l]
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a.emplace(-l, -r);
        b.emplace(r, l);
    }

    vector<int> ans(n + 1);
    int can = 0;
    int cnt = 0;
    while (can < n) {
        vector<pair<int, int>> ev; // [start, type]
        for (auto& [l, r] : a) {
            ev.emplace_back(-l, 1);
            ev.emplace_back(-r + 1, -1);
        }
        sort(all(ev));
        int c = 0;
        int ncan = 0;
        for (int i = 0; i < ev.size(); ++i) {
            c += ev[i].second;
            if (i == ev.size() - 1 || ev[i].first != ev[i + 1].first) {
                ncan = max(ncan, c);
            }
        }
        for (int i = can + 1; i <= ncan; ++i) {
            ans[i] = cnt;
        }
        can = ncan;

        cnt++;
        pair<int, int> seg1 = *a.begin();
        pair<int, int> seg2 = *b.begin();
        a.erase(seg1);
        a.erase({-seg2.second, -seg2.first});
        b.erase(seg2);
        b.erase({-seg1.second, -seg1.first});
        swap(seg2.first, seg2.second);
        seg1.first = -seg1.first;
        seg1.second = -seg1.second;
        swap(seg1, seg2);
        pair<int, int> ns1 = {seg1.first, seg2.first};
        pair<int, int> ns2 = {seg1.second, seg2.second};
        a.emplace(-ns1.first, -ns1.second);
        a.emplace(-ns2.first, -ns2.second);
        b.emplace(ns1.second, ns1.first);
        b.emplace(ns2.second, ns2.first);
    }
    while (q--) {
        int i;
        cin >> i;
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifdef LOCAL
    freopen("C:\\Users\\User\\Documents\\olymp\\input.txt", "r", stdin);
    freopen("C:\\Users\\User\\Documents\\olymp\\output.txt", "w", stdout);
    #endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}