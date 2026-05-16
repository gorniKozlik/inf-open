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
    vector<pair<int, int> > seg(n);
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].first >> seg[i].second;
    }
    sort(seg.begin(), seg.end());
    bool np = true;
    for (int i = 0; i + 1 < n; ++i) {
        if (seg[i].second >= seg[i + 1].first) {
            np = false;
            break;
        }
    }
    if (!np) {
        exit(-1);
    }
    vector<int> ans(n + 1, 0);
    for (int i = 1; i < min(n+1, 4); ++i) {
        ans[i] = 1;
    }
    int cnt = 2;
    for (int i = min(n, 4); i < n+1; i += 2) {
        ans[i] = cnt;
        if (i + 1 < n+1) {
            ans[i + 1] = cnt;
        }
        cnt++;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
