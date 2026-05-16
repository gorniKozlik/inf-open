#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(), x.end()
// #define int long long

const int N = 2e5 + 100;
const int INF = 1e9 + 7;

pair<pair<int, int>, int> tree[4 * N];

void upd(int v, int tl, int tr, int l, int r) {
    if (r <= tl || tr <= l) {
        return;
    }
    if (l <= tl && tr <= r) {
        if ((tl - l) % 2 == 0) {
            tree[v].F.F = min(tree[v].F.F, (tl - l) / 2 + 1);
        } else {
            tree[v].F.S = min(tree[v].F.S, (tl - l) / 2 + 1);
        }
        return;
    }
    int tm = (tl + tr) / 2;
    upd(2 * v, tl, tm, l, r);
    upd(2 * v + 1, tm, tr, l, r);
}

void upd2(int v, int tl, int tr, int l, int r, int val) {
    if (r <= tl || tr <= l) {
        return;
    }
    if (l <= tl && tr <= r) {
        tree[v].S = min(val + (tl - l) + 1, tree[v].S);
        return;
    }
    int tm = (tl + tr) / 2;
    upd2(2 * v, tl, tm, l, r, val);
    upd2(2 * v + 1, tm, tr, l, r, val);
}

int ans[N];

void rec(int v, int tl, int tr) {
    if (tr - tl == 1) {
        ans[tl] = min(tree[v].F.F, min(tree[v].F.S, tree[v].S));
    } else {
        int tm = (tl + tr) / 2;
        tree[2 * v].F.F = min(tree[2 * v].F.F, tree[v].F.F);
        tree[2 * v].F.S = min(tree[2 * v].F.S, tree[v].F.S);
        tree[2 * v].S = min(tree[2 * v].S, tree[v].S);
        if ((tm - tl) % 2 == 0) {
            tree[2 * v + 1].F.F = min(tree[2 * v + 1].F.F, tree[v].F.F + (tm - tl) / 2);
            tree[2 * v + 1].F.S = min(tree[2 * v + 1].F.S, tree[v].F.S + (tm - tl) / 2);
            tree[2 * v + 1].S = min(tree[2 * v + 1].S, tree[v].S + (tm - tl));
        } else {
            tree[2 * v + 1].F.F = min(tree[2 * v + 1].F.F, tree[v].F.S + (tm - tl) / 2 + 1);
            tree[2 * v + 1].F.S = min(tree[2 * v + 1].F.S, tree[v].F.F + (tm - tl) / 2);
            tree[2 * v + 1].S = min(tree[2 * v + 1].S, tree[v].S + (tm - tl));
        }
        rec(2 * v, tl, tm);
        rec(2 * v + 1, tm, tr);
    }
}

vector<pair<int, int> > v;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 4 * N; ++i) {
        tree[i] = {{INF, INF}, INF};
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int l, r;
        cin >> l >> r;
        v.pb({l, 0});
        v.pb({r, 1});
    }
    sort(all(v));
    int last = 0;
    int b = 0;
    int c = 0;
    int a = 0;
    int l = 0;
    int mx = 0;
    for (auto it: v) {
        if (it.F != last) {
            if (last != 0) {
                int x = a + b;
                mx = max(mx, x);
                int r = n - l - a - b;
                int y = 2 * min(l, r);
                int z = (r > l ? min(b, abs(r - l)) : min(c, abs(r - l)));
                upd(1, 0, n, x, x + y);
                upd2(1, 0, n, x + y, x + y + z, y / 2);
            }
            l += b;
            b = 0;
            c = 0;
            last = it.F;
        }
        if (it.S == 0) {
            ++a;
            ++c;
        } else {
            --a;
            ++b;
        }
    }
    rec(1, 0, n);

    for (int i = 0; i < mx; ++i) {
        ans[i] = 0;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k - 1] << " ";
    }
    return 0;
}
