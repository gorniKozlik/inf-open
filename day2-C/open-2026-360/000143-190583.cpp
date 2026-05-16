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
    while (q--) {
        int k;
        cin >> k;
        cout << max(0ll, k - 1) << '\n';
    }

    return 0;
}
