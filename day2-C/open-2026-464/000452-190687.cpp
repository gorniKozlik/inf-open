#include <bits/stdc++.h>

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

//#define D_GLIBCXX_DEBUG
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pii pair<int, int>

typedef long long ll;
typedef long double ld;

#define int long long

using namespace std;

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int mod = 998244353;
const int inf = 1e9 + 9;

int chk(vector<pii> & v) {
    vector<pii> sb;
    for (auto [x, y] : v) {
        sb.push_back({x, -1});
        sb.push_back({y, 1});
    }
    int b = 0, mx = 0;
    sort(all(sb));
    for (auto [x, tp] : sb) {
        b -= tp;
        mx = max(b, mx);
    }
    return mx;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    set<pii> st, f;

    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        st.insert({-a[i].first, i});
        f.insert({a[i].second, i});
    }
    vector<pii> qw(q);
    for (int i = 0; i < q; i++) {
        cin >> qw[i].first;
        qw[i].second = i;
    }
    vector<int> ans(n);
    sort(all(qw));

    int cnt = 0;
    for (int i = 0; i < n; i++) {

        while (chk(a) < qw[i].first) {
            int mnf = f.begin()->second;
            int mxs = st.begin()->second;
            f.erase(f.begin());
            st.erase(st.begin());
            swap(a[mnf].second, a[mxs].first);
            st.insert({-a[mxs].first, mxs});
            f.insert({a[mnf].second, mnf});
            cnt++;
        }
        ans[qw[i].second] = cnt;
    }
    for (auto i: ans) cout << i << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef Local
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // Local
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}