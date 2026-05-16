#include <bits/stdc++.h>
// #pragma GCC optimize("O3")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve();

void solve1() {
    auto start = clock();
    while (true) {
        auto now = clock();
        if ((now - start) / CLOCKS_PER_SEC > 1) {
            cout << 2;
            return;
        }
    }
}

int32_t main() {
#ifdef LOCAL
    freopen("Input.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n), cord;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        cord.emplace_back(l[i]);
        cord.emplace_back(r[i]);
    }
    sort(cord.begin(), cord.end());
    cord.resize(unique(cord.begin(), cord.end()) - cord.begin());
    vector<int> col(cord.size() + 1);
    for (int i = 0; i < n; ++i) {
        col[lower_bound(cord.begin(), cord.end(), l[i]) - cord.begin()]++;
        col[lower_bound(cord.begin(), cord.end(), r[i]) - cord.begin() + 1]--;
    }
    int nw = 0;
    for (int i = 0; i < col.size(); ++i) {
        nw += col[i];
        col[i] = nw;
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    vector<int> ans(n + 10, 1e9);
    int ind = 0;
    // for (int i: col) {
    //     ans[i] = 0;
    // }
    for (int c: cord) {
        int LEFT = lower_bound(r.begin(), r.end(), c) - r.begin(); // меньших
        int RIGHT = n - (lower_bound(l.begin(), l.end(), c) - l.begin()); // больших равных
        int tyt = n - LEFT - RIGHT;
        for (int i = 0; i <= min(LEFT, RIGHT); ++i, tyt += 2) {
            ans[tyt] = min(ans[tyt], i);
        }
        ind++;
    }
    nw = 1e9;
    for (int i = n + 9; i >= 0; --i) {
        nw = min(nw, ans[i]);
        ans[i] = nw;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << '\n';
    }
}
