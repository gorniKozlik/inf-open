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
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a.emplace_back(l, r);
    }

    vector<int> ans(n + 1);
    int can = 0;
    int cnt = 0;
    while (can < n) {
        vector<pair<int, int>> ev; // [start, type]
        for (auto& [l, r] : a) {
            ev.emplace_back(l, 1);
            ev.emplace_back(r + 1, -1);
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
        array<int, 3> mn = {-1, -1, -1};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    int val = f(a[i], a[j]);
                    if (mn[0] < val) {
                        mn = {val, i, j};
                    }
                }
            }
        }
        pair<int, int> ns1 = {a[mn[1]].first, a[mn[2]].first};
        pair<int, int> ns2 = {a[mn[1]].second, a[mn[2]].second};
        a[mn[1]] = ns1;
        a[mn[2]] = ns2;
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