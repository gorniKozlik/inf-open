#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 2 * 3e5 + 11;
const int mod = 998244353;
//#define int long long
int quer[N];
int f[2 * N], f2[2 * N];
void upd (int pos, int x) {
    pos = 2 * N - pos;
    for ( ; pos < 2 *  N; pos += (pos & -pos)) f[pos] = max (f[pos], x);
}
int get (int pos) {
    int mx = -1;
    ++pos;
    pos = 2 * N - pos;
    for ( ; pos >= 1; pos -= (pos & -pos)) mx = max (mx, f[pos]);
    return mx;
}
void upd2 (int pos, int x) {
    ++pos;
    for ( ; pos < 2 *  N; pos += (pos & -pos)) f2[pos] = max (f2[pos], x);
}
int get2 (int pos) {
    int mx = -1;
    for ( ; pos >= 1; pos -= (pos & -pos)) mx = max (mx, f2[pos]);
    return mx;
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
    vector<int> ans (n + 1, n);
    for (int i = 0; i <= mx; ++i) {
        upd (2 * quer[i] + i, i);
        upd2 (2 * quer[i] + i, i + quer[i]);
    }

    for (int k = mx + 1; k <= n; ++k) {
        int g = get (k);
        if (g != -1) {
            ans[k] = min (ans[k], (k - g + 1) / 2);
        }
//        ans[k] =  min (ans[k], k - get2 (k - 1));
        for (int i = 0; i <= mx; ++i) {
            if (2 * quer[i] + i >= k) {
//                ans[k] = min (ans[k], (k - i + 1) / 2);
                continue;
            } else {
                ans[k] = min (ans[k], k - i - quer[i]);
            }
        }
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) {
            cout << "0 ";
            continue;
        }
        cout << ans[k] << ' ';
    }
    cout << '\n';
}
