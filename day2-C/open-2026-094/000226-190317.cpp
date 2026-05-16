#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#define int long long
#define ff first
#define ss second
#define endl "\n"
#define all(x) x.begin(), x.end()
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update<>>

const int MOD = 998244353;
const int INF = 1e18;


void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> nums;

    vector<pair<int, int> > a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i].ff >> a[i].ss;
        nums.push_back(a[i].ff);
        nums.push_back(a[i].ss);
    }

    sort(all(nums));

    for (int i = 0; i < n; i++) {
        a[i].ff = lower_bound(all(nums), a[i].ff) - nums.begin();
        a[i].ss = lower_bound(all(nums), a[i].ss) - nums.begin();
    }

    while (q--) {
        int x;
        cin >> x;

        int ans = INF;

        for (int i = 0; i < 2 * n - 1; i++) {
            int good = 0;
            int left = 0;
            int right = 0;
            for (auto it: a) {
                if (it.ff <= i && it.ss > i) {
                    good++;
                } else if (it.ss <= i) {
                    left++;
                } else {
                    right++;
                }
            }
            if (good >= x) {
                ans = 0;
            } else {
                int delt = x - good;
                if (delt <= min(left, right) * 2) {
                    ans = min(ans, (delt + 1) / 2);
                }
            }
        }
        cout << ans << " ";
    }
}


signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }
}
