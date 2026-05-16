#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define f first
#define s second
#define pb push_back
#define pf push_front
#define in insert
#define elif else if
#define nl '\n'

typedef __int128 int128;
typedef long double ld;
#define  long  int64_t
#define ulong uint64_t
#define uint  uint32_t

using namespace std;
using namespace __gnu_pbds;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template <class T>
using oset = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long

const int N = 1e6 + 9, oo = 1e18;

vector <int> v;
multiset <int> st;
vector <pair <int, int>> w;
int n, q, ans[N], l[N], r[N], cntL[N], cntR[N];

int32_t main() {
    cin.tie(0); ios::sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        v.pb(l[i]);
        v.pb(r[i]);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 0; i < n; ++i) {
        l[i] = lower_bound(v.begin(), v.end(), l[i]) - v.begin();
        r[i] = lower_bound(v.begin(), v.end(), r[i]) - v.begin();
        if (l[i] > 0)
            ++cntR[l[i] - 1];
        if (r[i] + 1 < v.size())
            ++cntL[r[i] + 1];
//        cout << l[i] << " " << r[i] << nl;
    }
    for (int i = 1; i < v.size(); ++i)
        cntL[i] += cntL[i - 1];
    for (int i = v.size() - 2; i >= 0; --i)
        cntR[i] += cntR[i + 1];
    for (int i = 0; i < v.size(); ++i) {
        int cnt = n - cntL[i] - cntR[i], pl = min(cntL[i], cntR[i]);
//        cout << i << ": " << cnt << " " << pl << nl;
        w.pb({cnt, -1});
        w.pb({cnt + pl * 2 + 1, cnt});
    }
    sort(w.begin(), w.end());
    fill(ans, ans + N, oo);
    for (int i = 0, j = 0; i <= n; ++i) {
        while (j < w.size() && w[j].f == i) {
            if (w[j].s == -1)
                st.in(w[j].f);
            else
                st.erase(st.find(w[j].s));
            ++j;
        }
        if (st.size())
            ans[i] = (i - *prev(st.end()) + 1) / 2;
    }
    if (ans[n] == oo)
        ans[n] = ans[n - 1] + 1;
//    for (int i = 1; i <= n; ++i)
//        cout << ans[i] << " ";
//    cout << nl;
    for (int i = n - 1; i >= 1; --i)
        ans[i] = min(ans[i], ans[i + 1]);
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}
