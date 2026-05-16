#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
#define int long long
using ll = long long;
using namespace std;
// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//  using ordered_set = tree<int, null_type, less<int>, rb_tree_tag,
//  tree_order_statistics_node_update>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int c1 = 0, c2 = 0;
    for (auto& x : a) {
        if (x & 1)
            c1++;
        else
            c2++;
    }
    if (c1 == 0 || c2 == 0)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}
