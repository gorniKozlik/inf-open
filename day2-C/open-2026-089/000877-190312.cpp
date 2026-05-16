#include <bits/extc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2") 
#define int long long

using namespace std;
using namespace __gnu_pbds;

const int inf = 1e12;

struct segtree {
    int n;
    vector<int> t, add;

    segtree(int _n) {
        n = _n;
        t.resize(4 * n, 0);
        add.resize(4 * n, 0);
    }

    void push(int v, int l, int r) {
        if (add[v] != 0) {
            t[v] += add[v];
            if (l + 1 != r) {
                add[2 * v + 1] += add[v];
                add[2 * v + 2] += add[v];
            }
            add[v] = 0;
        }
    }

    void update(int v, int l, int r, int ql, int qr) {
        push(v, l, r);
        if (ql <= l && r <= qr) {
            ++add[v];
            push(v, l, r);
        } else if (qr <= l || r <= ql) {
            return;
        } else {
            int m = (l + r) / 2;
            update(2 * v + 1, l, m, ql, qr);
            update(2 * v + 2, m, r, ql, qr);
            t[v] = max(t[2 * v + 1], t[2 * v + 2]);
        }
    }

    void update(int l, int r) {
        update(0, 0, n, l, r);
    }

    int query(int v, int l, int r, int ql, int qr) {
        push(v, l, r);
        if (ql <= l && r <= qr) {
            return t[v];
        } else if (qr <= l || r <= ql) {
            return -inf;
        } else {
            int m = (l + r) / 2;
            return max(query(2 * v + 1, l, m, ql, qr),
                        query(2 * v + 2, m, r, ql, qr));
        }
    }

    int query() {
        push(0, 0, n);
        return t[0];
    }
}; 

void solve() {
    int n, q; cin >> n >> q;
    vector<int> l(n), r(n);
    vector<int> srtx;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        srtx.push_back(l[i]);
        srtx.push_back(r[i]);
    }
    sort(srtx.begin(), srtx.end());
    unordered_map<int, int> comp;
    for (int i = 0; i < 2 * n; ++i) {
        comp[srtx[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        l[i] = comp[l[i]];
        r[i] = comp[r[i]];
    }
    segtree t(2 * n);
    for (int i = 0; i < n; ++i) {
        t.update(l[i], r[i] + 1);
    }
    set<int> ls, rs;
    for (int i = 0; i < n; ++i) {
        ls.insert(l[i]);
        rs.insert(r[i]);
    }
    vector<int> ans(n + 1, inf);
    int cur = t.query();
    ans[cur] = 0;
    int op = 0;
    while (cur < n) {
        ++op;
        auto ri = *rs.begin();
        rs.erase(rs.begin());
        auto li = *(--ls.end());
        ls.erase(li);
        t.update(ri, li);
        t.update(ri + 1, li + 1);
        cur = t.query();
        ans[cur] = min(ans[cur], op);
    }
    for (int i = n - 1; i >= 1; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < q; ++i) {
        int k; cin >> k;
        cout << ans[k] << ' ';
    }
    cout << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}