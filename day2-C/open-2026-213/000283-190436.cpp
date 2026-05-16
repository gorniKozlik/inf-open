#ifndef LOCAL
#pragma GCC Optimize("O3, Ofast")
#pragma GCC Target("avx,avx2,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

#define int ll
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#ifndef LOCAL
#define endl "\n"
#endif

struct F {
    vector<int> t;
    F(int n) {
        t.assign(n, 0);
    }
    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r&(r + 1)) - 1) {
            ans += t[r];
        }
        return ans;
    }
    void upd(int i, int x) {
        for (; i < t.size(); i = (i|(i + 1))) {
            t[i] += x;
        }
    }
};

mt19937 rnd(time(0));

const int MAX_N = (1<<3);

struct Node {
    int x, tp;
    Node() {
        x = 0;
        tp = 0;
    }
};
struct ST1 {
    pii T[MAX_N * 2];
    ST1() {
        for (int i = 0; i < MAX_N * 2; ++i) {
            T[i] = mp(1e9, 1e9);
        }
    }
    void upd(int i, int x) {
        i += MAX_N;
        T[i] = mp(x, i - MAX_N);
        while (i > 1) {
            i /= 2;
            T[i] = min(T[i * 2], T[i * 2 + 1]);
        }
    }
};
struct ST2 {
    Node T[MAX_N * 4];
    void push(int i, int x) {
        T[i].x += x;
        T[i].tp += x;
    }
    void push(int i) {
        push(i * 2, T[i].tp);
        push(i * 2 + 1, T[i].tp);
        T[i].tp = 0;
    }
    void update(int i, int l, int r, int ql, int qr, int qx) {
        if (l >= qr || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            push(i, qx);
        } else {
            int m = (l + r) / 2;
            push(i);
            update(i * 2, l, m, ql, qr, qx);
            update(i * 2 + 1, m, r, ql, qr, qx);
            T[i].x = max(T[i * 2].x, T[i * 2 + 1].x);
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    vector<int> xes;
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].f >> seg[i].s;
        xes.pb(seg[i].f);
        xes.pb(seg[i].s);
    }
    sort(all(xes));
    auto smaller = [&](int x) {
        return lower_bound(all(xes), x) - xes.begin();
    };
    ST1 L, R;
    ST2 A;
    int ind = 0;
    for (auto &x : seg) {
        x.f = smaller(x.f);
        x.s = smaller(x.s);
        A.update(1, 0, n * 2, x.f, x.s, 1);
        L.upd(ind, x.s);
        R.upd(ind, -x.f);
        ++ind;
    }
    auto calc = [&]() {
        return A.T[1].x;
    };
    vector<int> ans(n + 1);
    int now = calc();
    for (int i = now + 1; i <= n; ++i) {
        ans[i] = 1e9;
    }
    int cnt = 0;
    while (true) {
        int l = L.T[1].s;
        int r = R.T[1].s;
        if (l == 1e9 || r == 1e9) {
            break;
        }
        if (seg[l].s < seg[r].f) {
            A.update(1, 0, n * 2, seg[l].s, seg[r].f, 2);
            ++cnt;
            int was = seg[l].s;
            seg[l].s = seg[r].f;
            seg[r].f = was;
            L.upd(l, 1e9);
            R.upd(r, 1e9);
            int res = calc();
            for (int i = now + 1; i <= res; ++i) {
                ans[i] = cnt;
            }
            now = res;
        } else {
            break;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << endl;
}

signed main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ios::sync_with_stdio(false);
        cin.tie(0);
    #endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}