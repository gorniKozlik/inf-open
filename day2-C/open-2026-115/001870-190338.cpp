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
int quer[N];int f (int i, int k) {
    int delta = k - i;
    int op = min ((delta + 1) / 2, quer[i]);
    delta -= 2 * op;
    delta = max (delta, 0);
    return delta + op;
}
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

        int mx = 0;
    vector<int> A;
    vector<int> cR (n);
    for (int i = 0; i < n; ++i) {
        A.push_back(a[i].first);
    }
    sort (begin (A), end (A));
    for (int i = 0; i < n; ++i) {
        int id = upper_bound(begin (A), end (A), a[i].second) - begin (A);
        cR[i] = (int)A.size() - id;
    }
    A.clear();
    vector<int> cL (n);
    for (int i = 0; i < n; ++i) {
        A.push_back(a[i].second);
    }
    sort (begin (A), end (A));
    for (int i = 0; i < n; ++i) {
        int id = upper_bound(begin (A), end (A), a[i].first) - begin (A);
        cL[i] = id;
    }
    oset<pair<int,int>> B;
    for (int mxL = 0; mxL < n; ++mxL) {
        int id = -1;
        auto it = st.lower_bound ({a[mxL].first, -1});
        if (it == st.end()) id = -1;
        else id = (*it).second;
        B.insert({a[mxL].second, mxL});
        if (id != -1) {
            int mnR = id;
            int cnt = 0, c1 = cR[mnR], c2 = cL[mxL];
            cnt = (int)B.size() - B.order_of_key({a[mnR].second, -1});
            mx = max (mx, cnt);
            quer[cnt] = max (quer[cnt], min (c1, c2));
        }
    }
    for (int i = mx - 1; i >= 0; --i) quer[i] = max (quer[i], quer[i + 1]);
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) {
            cout << "0 ";
            continue;
        }
        int ans = n;
        int l = 0, r = mx;
        while (r - l + 1 > 500) {
            int m1 = l + (r - l + 1) / 3;
            int m2 = r - (r - l + 1) / 3;
            if (f(m1, k) < f (m2, k)) r = m2;
            else l = m1;
        }
        for (int i = l; i <= r; ++i)  ans = min (ans, f (i, k));
        for (int i = 0; i <= min (mx, 100); ++i) ans = min (ans, f (i, k));
        for (int i = mx; i >= max (0, mx - 100); --i) ans = min (ans, f(i, k));
        cout << ans << ' ';
    }
    cout << '\n';
}
