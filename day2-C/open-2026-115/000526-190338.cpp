#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 3e5 + 11;
const int mod = 998244353;
#define int long long

signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort (begin (a), end (a));
    while (q--) {
        int k;
        cin >> k;
        int mx = 0;
        int ans = n;
        for (int mxL = 0; mxL < n; ++mxL) {
            for (int mnR = 0; mnR <= mxL; ++mnR) {
                if (a[mnR].second < a[mxL].first) continue;
                int cnt = 0, c1 = 0, c2 = 0;
                for (int i = 0; i < n; ++i) {
                    if (a[i].first <= a[mnR].second && a[i].second >= a[mxL].first) ++cnt;
                    if (a[i].first > a[mnR].second) ++ c1;
                    if (a[i].second < a[mxL].first) ++c2;
                }
                int delta = (k - cnt);
                int op = min ({c1, c2, (delta + 1) / 2});
                delta -= 2 * op;
                delta = max (0LL, delta);
                ans = min (ans, op + delta);
            }
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
