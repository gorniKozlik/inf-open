#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
#define int long long
using ll = long long;
using namespace std;
// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//  using ordered_set = tree<int, null_type, less<int>, rb_tree_tag,
//  tree_order_statistics_node_update>;
// kamir
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> tmp(n);
    for (auto& [x, y] : tmp) cin >> x >> y;
    vector<int> ans(n + 1, 0);

    sort(tmp.begin(), tmp.end());

    auto ff = [&]() -> int {
        vector<pair<int, int>> sb;
        for (int i = 0; i < n; ++i) {
            sb.push_back({tmp[i].first, -1});
            sb.push_back({tmp[i].second, 1});
        }
        sort(sb.begin(), sb.end());
        int maxn = 0;
        int cur = 0;
        for (int i = 0; i < 2 * n; ++i) {
            cur -= sb[i].second;
            maxn = max(maxn, cur);
        }
        return maxn;
    };

    auto check = [&](int i, int j) -> bool {
        auto [l1, r1] = tmp[i];
        auto [l2, r2] = tmp[j];
        return ((l1 >= l2 && l1 <= r2) || (l2 >= l1 && l2 <= r1));
    };
    int cur = ff();
    for (int i = 0; i <= cur; ++i) {
        ans[i] = 0;
    }
    int it = 0;
    while (cur < n) {
        if (it > n - it - 1)
            break;
        if (!check(it, n - it - 1)) {
            auto [l1, r1] = tmp[it];
            auto [l2, r2] = tmp[n - it - 1];
            tmp[it].second = l2;
            tmp[n - it - 1].first = r1;
            int c = ff();
            for (int i = cur + 1; i <= c; ++i) ans[i] = it + 1;
            cur = c;
        } else {
            it++;
        }
    }

    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }

    return 0;
}
