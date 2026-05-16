#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

int inf = (int)1000 * 1000 * 1000 * 1000 * 1000 * 1000 + 100;
// int inf = (int)1000 * 1000 * 1000 + 100;

/*
#pragma optimize("O3")
#pragma optimize("avx,avx2,bmi,bmi2")
*/

mt19937_64 rnd(228);

void print(vector <int> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << '\n';
}

struct st {
    vector <int> t;
    vector <int> p;

    void build(int n) {
        t.resize(4 * n, inf);
        p.resize(4 * n, inf);
    }

    void push(int v) {
        if (p[v] == inf) {
            return;
        }
        p[v * 2 + 1] = min(p[v * 2 + 1], p[v]);
        p[v * 2 + 2] = min(p[v * 2 + 2], p[v]);

        t[v * 2 + 1] = min(t[v * 2 + 1], p[v]);
        t[v * 2 + 2] = min(t[v * 2 + 2], p[v]);

        p[v] = inf;
    }

    int get(int v, int l, int r, int ll, int rr) {
        if (ll > rr) {
            return inf;
        }
        if (l == ll && r == rr) {
            return t[v];
        }
        push(v);
        int m = (l + r) / 2;
        return min(get(v * 2 + 1, l, m, ll, min(m, rr)), get(v * 2 + 2, m + 1, r, max(m + 1, ll), rr));
    }

    void update(int v, int l, int r, int ll, int rr, int x) {
        if (ll > rr) {
            return;
        }
        if (l == ll && r == rr) {
            t[v] = min(t[v], x);
            p[v] = min(p[v], x);
            return;
        }
        int m = (l + r) / 2;
        push(v);
        update(v * 2 + 1, l, m, ll, min(m, rr), x);
        update(v * 2 + 2, m + 1, r, max(m + 1, ll), rr, x);
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector <int> l(n);
    vector <int> r(n);
    for (int i = 0; i < n; i ++) {
        cin >> l[i] >> r[i];
    }

    vector <pair <int, int>> t;
    for (int i = 0; i < n; i ++) {
        t.push_back({l[i], 1});
        t.push_back({r[i], -1});
    }

    sort(t.begin(), t.end());

    vector <int> ans(n + 1, inf);

    int mx = -1;

    st t1;
    t1.build(n + 1);

    st t2;
    t2.build(n + 1);

    int cnt = 0;
    for (int i = 0; i < t.size(); i ++) {
        cnt += t[i].second;
        int a = ((i + 1) - cnt) / 2;
        int b = ((t.size() - i - 1) - cnt) / 2;
        // for (int j = 0; j <= cnt; j ++) {
        //     ans[j] = 0;
        // }
        mx = max(mx, cnt);

        // for (int j = cnt + 1; j <= cnt + min(a, b) * 2; j ++) {
        //     // ans[j] = min(ans[j], (j - cnt + 1) / 2);
        //     ans[j] = min(ans[j], j + (1 - cnt));
        // }
        t1.update(0, 0, n, cnt + 1, cnt + min(a, b) * 2, 1 - cnt);
        // for (int j = cnt + min(a, b) * 2 + 1; j <= n; j ++) {
        //     // ans[j] = min(ans[j], min(a, b) + (j - cnt - min(a, b) * 2));
        //     ans[j] = min(ans[j], j * 2 + (- cnt * 2 - min(a, b) * 2));
        // }
        t2.update(0, 0, n, cnt + min(a, b) * 2 + 1, n, (-cnt * 2 - min(a, b) * 2));
    }

    for (int i = 0; i <= mx; i ++) {
        ans[i] = 0;
    }
    for (int i = 0; i <= n; i ++) {
        ans[i] = min(ans[i], i + t1.get(0, 0, n, i, i));
    }
    for (int i = 0; i <= n; i ++) {
        ans[i] = min(ans[i], i * 2 + t2.get(0, 0, n, i, i));
    }

    while (q --) {
        int x;
        cin >> x;
        cout << ans[x] / 2 << " ";
    }
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif

    int _ = 1;
    // cin >> _;
    while (_ --) {
        solve();
    }
}