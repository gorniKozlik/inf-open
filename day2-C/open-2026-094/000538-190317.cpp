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

    int open = 0;
    int close = 0;

    vector<vector<int> > sl(2 * n);

    for (auto it: a) {
        sl[it.ff].push_back(1);
        sl[it.ss].push_back(-1);
    }

    deque<pair<int, int> > vls;

    for (int i = 0; i < 2 * n - 1; i++) {
        for (auto it: sl[i]) {
            if (it == 1) {
                open++;
            } else {
                open--;
                close++;
            }
        }
        int left = close;
        int good = open;
        int right = n - good - left;
        vls.push_back({min(left, right) * 2 + good, good});
    }

    sort(all(vls));

    multiset<int> st;

    for (auto it: vls) {
        st.insert(it.ss);
    }

    vector<int> ans(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        while (vls.size() && vls.front().ff < i) {
            st.extract(vls.front().ss);
            vls.pop_front();
        }
        int best = *(st.rbegin());
        if (best >= i) {
            ans[i] = 0;
        } else {
            int delt = i - best;
            ans[i] = (delt + 1) / 2;
        }
    }

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
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
