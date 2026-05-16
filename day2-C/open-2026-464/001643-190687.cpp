#include <bits/stdc++.h>

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("fast-math")
// #pragma GCC optimize("no-stack-protector")

//#define D_GLIBCXX_DEBUG
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pii pair<int, int>

typedef long long ll;
typedef long double ld;

//#define int long long

using namespace std;

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int mod = 998244353;
const int inf = 1e9 + 9;
const int mxn = 2e5 +69;

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

int tree[mxn * 4], add[mxn * 4];

void push(int i, int l, int r) {
    if (add[i] == 0) return;
    tree[i] += add[i];
    if (r != l + 1) {
        add[2 * i + 1] += add[i];
        add[2 * i + 2] += add[i];
    }
    add[i] = 0;
    return;
}

void upd(int i, int l, int r, int ql, int qr, int val) {
    push(i, l, r);
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        add[i] += val;
        push(i, l, r);
        return;
    }
    int m = (r - l) / 2 + l;
    upd(2 * i + 1, l, m, ql, qr, val);
    upd(2 * i + 2, m, r, ql, qr, val);
    tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    return;
}
int get(int i, int l, int r, int ql, int qr) {
    push(i, l, r);
    if (ql <= l && r <= qr) return tree[i];
    if (qr <= l || r <= ql) return 0;
    int m = (r - l) / 2 + l;
    int v1 = get(2 * i + 1, l, m, ql, qr);
    int v2 = get(2 * i + 2, m, r, ql, qr);
    return max(v1, v2);
}

void upd(int l, int r, int v) {
    if (r <= l) return;
    upd(0, 0, mxn, l, r, v);
    return;
}
int get(int l, int r) {
    return get(0, 0, mxn, l, r);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    set<pii> st, f;

    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        upd(a[i].first, a[i].second + 1, 1);
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

        while (get(0, mxn) < qw[i].first) {
            int mnf = f.begin()->second;
            int mxs = st.begin()->second;
            if (a[mnf].second >= a[mxs].first) continue;
            upd(a[mnf].second + 1, a[mxs].first, 2);
            upd(a[mnf].second, a[mnf].second + 1, 1);
            upd(a[mxs].first, a[mxs].first + 1, 1);
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
