#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast,unroll-loops,O3")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    pair<int, int> lr[n];

    for (pair<int, int>& i : lr) {
        cin >> i.first >> i.second;
    }

    int ans[n + 1];
    ans[1] = 0;

    for (int i = 2; i <= n; i += 2) {
        ans[i] = ans[i - 1] + 1;
        if (i != n) {
            ans[i + 1] = ans[i];
        }
    }

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}
