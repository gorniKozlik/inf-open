#include <bits/stdc++.h>

#define int long long

using namespace std;

constexpr int N = 2e5 + 10, L = 20;

int t[8 * N], add[8 * N];

int prefix[2 * N];

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = prefix[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

void push(int v) {
    t[v * 2] += add[v];
    add[v * 2] += add[v];
    t[v * 2 + 1] += add[v];
    add[v * 2 + 1] += add[v];
    add[v] = 0;
}

void upd(int v, int l, int r, int ql, int qr, int d) {
    if (r < ql || l > qr) {
        return;
    }
    if (l >= ql && r <= qr) {
        t[v] += d;
        add[v] += d;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    upd(v * 2, l, m, ql, qr, d);
    upd(v * 2 + 1, m + 1, r, ql, qr, d);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int> > a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.emplace(x, 1);
        a.emplace(y, -1);
    }
    vector<int> b;
    for (auto [x, tp]: a) {
        if (tp == 1) {
            b.push_back(1);
        } else {
            b.push_back(-1);
        }
    }
    prefix[0] = b[0];
    int ind = 1;
    for (int i = 1; i < 2 * n; ++i) {
        prefix[i] = prefix[i - 1] + b[i];
        ind = max(ind, prefix[i]);
    }
    build(1, 0, 2 * n - 1);
    vector<int> ans(n + 1);
    for (int i = 1; i <= ind; ++i) {
        ans[i] = 0;
    }
    ind++;
    int i = 0, j = 2 * n - 1;
    int cnt = 0;
    while (i < j) {
        while (i < 2 * n && b[i] == 1) {
            i++;
        }
        while (j >= 0 && b[j] == -1) {
            j--;
        }
        if (i > j) break;
        cnt++;
        upd(1, 0, 2 * n - 1, i, j - 1, 2);
        if (i + 1 == j) {
            for (int k = ind; k <= n; ++k) {
                ans[k] = cnt;
            }
        } else {
            int next = t[1];
            for (int k = ind; k <= next; ++k) {
                ans[k] = cnt;
            }
            ind = next + 1;
        }
        i++, j--;
    }
    for (int k = ind; k <= n; ++k) {
        ans[k] = cnt;
    }
    for (int e = 0; e < q; ++e) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int dota = 1;
    //cin >> dota;
    while (dota--) {
        solve();
        cout << '\n';
    }
    return 0;
}
