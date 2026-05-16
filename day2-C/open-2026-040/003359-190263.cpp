#include <bits/stdc++.h>

//
//God Bless Me /(^_^)/
//

using namespace std;
using ll = long long;
using ld = long double;

const int mod = 1e9 + 7;
const int maxn = 2e5 + 1;

struct node {
    int sm = 0;
    int mx = 0;
};

vector<node> tree;

void upd(int x, int l, int r, int ql, int qr, int ch) {
    if (r < ql || l > qr) return;

    if (ql <= l && r <= qr) {
        tree[x].sm += ch;
        tree[x].mx += ch;
        return;
    }

    int y = (l + r) >> 1;
    int z = x + (y - l + 1) * 2;

    upd(x + 1, l, y, ql, qr, ch);
    upd(z, y + 1, r, ql, qr, ch);

    tree[x].mx = max(tree[x + 1].mx, tree[z].mx) + tree[x].sm;
}

int get() {
    return tree[0].mx;
}

void solve() {
    int n, q; cin >> n >> q;

    vector<int> l(n), r(n), lr;
    lr.reserve(2 * n + 1);
    vector<int> id(n);
    for (int i{}; i < n; i++) {
        cin >> l[i] >> r[i];
        lr.push_back(l[i]);
        lr.push_back(r[i]);
        id[i] = i;
    }

    sort(lr.begin(), lr.end());
    lr.erase(unique(lr.begin(), lr.end()), lr.end());

    for (auto &i : l) i = lower_bound(lr.begin(), lr.end(), i) - lr.begin();
    for (auto &i : r) i = lower_bound(lr.begin(), lr.end(), i) - lr.begin();

    tree.resize(4 * n + 1);

    for (int i{}; i < n; i++) {
        upd(0, 0, 2 * n - 1, l[i], r[i], 1);
    }

    sort(id.begin(), id.end(), [&](int a, int b) {
        return l[a] < l[b];
    });

    int k = 2;
    vector<int> ans(n + 1);
    ans[0] = 0;
    ans[1] = 0;
    while (k <= get()) {
        ans[k++] = 0;
    }
    int cnt = 0;

    int j = n - 1;
    for (int i{}; i < n; i++) {
        if (j <= i) break;
        if (r[id[i]] > l[id[j]] || r[id[i]] > r[id[j]]) continue;
        upd(0, 0, 2 * n - 1, l[id[i]], r[id[i]], -1);
        upd(0, 0, 2 * n - 1, l[id[j]], r[id[j]], -1);

        cnt++;
        upd(0, 0, 2 * n - 1, l[id[i]], r[id[j]], 1);
        upd(0, 0, 2 * n - 1, r[id[i]], l[id[j]], 1);
        j--;
        while (k <= get()) {
            ans[k++] = cnt;
        }
    }

    while (q--) {
        int x; cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int it = 1;

    //cin >> it;

    while (it--) {
        solve();
    }
}