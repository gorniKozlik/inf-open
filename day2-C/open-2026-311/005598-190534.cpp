#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("Ofast")
using ll = long long;
using ld = long double;
using vl = __int128_t;
using ull = unsigned long long;
#define pb emplace_back
#define all(x) (x).begin(), (x).end()
constexpr int mod = 998244353;
struct segtree {
    vector<int> tree;
    segtree(int n) {
        tree.resize(n * 4);
    }
    void update(int v, int l, int r, int i, int x) {
        if (l == r - 1) {
            tree[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, x);
        } else {
            update(2 * v + 2, m, r, i, x);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
    int get(int v, int l, int r, int ql, int qr) {
        if (ql >= r || l >= qr) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return tree[v];
        }
        int m = (l + r) / 2;
        return get(2 * v + 1, l, m, ql, qr) + get(2 * v + 2, m, r, ql, qr);
    }
};
void solve() {
    int n, q;
    cin >> n>> q;
    vector<pair<int,int>> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
        b.pb(x);
        b.pb(y);
    }
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    for (auto &[l, r] : a) {
        l = lower_bound(all(b), l) - b.begin();
        r = lower_bound(all(b), r) - b.begin();
    }
    sort(all(a));
    vector<int> ans(n + 1, n);
    vector<int> mdif(n + 1, n);
    const int N = 2 * n;
    segtree st(N);
    for (int i = 0; i < n; ++i) {
        // max li;
        int gt = st.get(0, 0, N, a[i].first, N);
        int sz = 1 + gt, lft = i - gt, rgt = n - i - 1;
        st.update(0, 0, N, a[i].second, 1);
        ans[sz] = 0;
        int x = sz + 2, cur = 1;
        while (x <= min(n, 10) && min(lft, rgt) > 0) {
            ans[x] = min(ans[x], cur++);
            lft--;
            rgt--;
            x += 2;
        }
        --x;
        for (; x <= min(n, 10) && max(lft, rgt) > 0;) {
            ans[x] = min(ans[x], cur++);
            lft--;
            rgt--;
            x++;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
