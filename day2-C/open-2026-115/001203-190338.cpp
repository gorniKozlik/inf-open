#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 3e5 + 11;
const int mod = 998244353;
//#define int long long

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
    set<pair<int,int>> st;
    for (int mxL = 0; mxL < n; ++mxL)
        st.insert ({a[mxL].second, mxL});
    vector<int>quer (n + 1);
        int mx = 0;
    for (int mxL = 0; mxL < n; ++mxL) {
        int id = -1;
        auto it = st.lower_bound ({a[mxL].first, -1});
        if (it == st.end()) id = -1;
        else id = (*it).second;
        if (id != -1) {
            int mnR = id;
            int cnt = 0, c1 = 0, c2 = 0;
            for (int i = 0; i < n; ++i) {
                if ((i <= mxL || a[i].first == a[mxL].first) && a[i].second >= a[mnR].second) ++cnt;
                if (a[i].first > a[mnR].second) ++ c1;
                if (a[i].second < a[mxL].first) ++c2;
            }
            mx = max (mx, cnt);
            quer[cnt] = max (quer[cnt], min (c1, c2));
        }
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) {
            cout << "0 ";
            continue;
        }
        int ans = n;
        for (int i = 0; i <= mx; ++i) {
            int delta = k - i;
            int op = min ((delta + 1) / 2, quer[i]);
            delta -= 2 * op;
            delta = max (delta, 0);
            ans = min (ans, op + delta);
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
