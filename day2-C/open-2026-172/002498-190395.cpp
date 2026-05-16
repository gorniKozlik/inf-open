#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz(x) (int)(x.size())

constexpr int N = 1e7;
constexpr int inf = 1e18;
constexpr int mod = 998244353;

int n;
vector<int> t, add;
map<int, int> nw;

void compress(vector<int> &x) {
    sort(all(x));
    for (auto i : x) {
        nw[i] = sz(nw);
    }
}

void push(int v) {
    t[v * 2 + 1] += add[v];
    t[v * 2 + 2] += add[v];
    add[v * 2 + 1] += add[v];
    add[v * 2 + 2] += add[v];
    add[v] = 0;
}

void upd(int ql, int qr, int x, int v = 0, int l = 0, int r = 2 * n) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        t[v] += x;
        add[v] += x;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    upd(ql, qr, x, v * 2 + 1, l, m);
    upd(ql, qr, x, v * 2 + 2, m, r);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> n >> q;
    vector<int> ans(n + 1);
    int idx = 1;
    vector<pair<int, int>> a, b;
    vector<int> l(n), r(n), x;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        x.push_back(l[i]);
        x.push_back(r[i]);
        a.push_back({l[i], i});
        b.push_back({r[i], i});
    }
    sort(all(a));
    sort(all(b));
    compress(x);
    int p1 = n - 1, p2 = 0;
    vector<bool> used(n, false);
    t.assign(4 * 2 * n, 0);
    add.assign(4 * 2 * n, 0);
    for (int i = 0; i < n; i++) {
        upd(nw[l[i]], nw[r[i]] + 1, 1);
    }
    while (idx <= t[0]) {
        ans[idx] = 0;
        idx++;
    }
    for (int i = 0; i < n; i++) {
        while (p1 >= 0 && used[a[p1].second]) {
            p1--;
        }
        while (p2 < n && used[b[p2].second]) {
            p2++;
        }
        if (p1 <= 0) {
            break;
        }
        used[a[p1].second] = true;
        used[b[p2].second] = true;
        upd(nw[l[a[p1].second]], nw[r[a[p1].second]] + 1, -1);
        upd(nw[l[b[p2].second]], nw[r[b[p2].second]] + 1, -1);
        upd(nw[l[b[p2].second]], nw[r[a[p1].second]] + 1, 1);
        upd(nw[r[b[p2].second]], nw[l[a[p1].second]] + 1, 1);
        while (idx <= t[0]) {
            ans[idx] = i + 1;
            idx++;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
    cout << endl;
    return 0;
}
