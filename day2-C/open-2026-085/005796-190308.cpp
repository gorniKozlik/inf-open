#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
using ll = long long;
constexpr int maxn = 5e5 + 3, mod = 1e9 + 7, inf = 1e9;
constexpr ll big_inf = 1e16;
constexpr __int128_t bnf = 1e30;
mt19937 rng(122);

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

struct segtr {
    struct node {
        int sm;
    };

    int n{};
    vector<node> t;
    vector<int> a;

    node merge(node a, node b) {
        node c{};
        c.sm = a.sm + b.sm;
        return c;
    }

    void build(int v, int tl, int tr) {
        if (tl + 1 == tr) {
            t[v].sm = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm, tr);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }

    segtr(int sz, vector<int> &b) {
        a = b;
        int k = 1;
        while (k < sz) {
            k *= 2;
        }
        n = k;
        t.assign(2 * n + 1, {0});
        build(1, 1, n + 1);
    }

    node get(int v, int tl, int tr, int ql, int qr) {
        if (tl >= qr || ql >= tr) {
            return {0};
        }
        if (ql <= tl && tr <= qr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, ql, qr),
                     get(v * 2 + 1, tm, tr, ql, qr));
    }

    void upd(int v, int tl, int tr, int ps, int x) {
        if (ps < tl || ps >= tr)
            return;
        if (tl + 1 == tr) {
            t[v].sm = x;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, ps, x);
        upd(v * 2 + 1, tm, tr, ps, x);
        t[v] = merge(t[v * 2], t[v * 2 + 1]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    ordered_set st;
    int cnt = 0;
    vector<int> res(n + 1, inf);
    // for (auto [l, r]: a) {
    //     cnt++;
    //     int jk = cnt - st.order_of_key(l) ;
    //     st.insert(r);
    //     for (int i = 1; i <= jk; i++) {
    //         res[i] = 0;
    //     }
    //     int gg = 1, cc = 0;
    //     //cout << cnt - jk << ' ' << n - cnt << '\n';
    //     for (int i = 1; i <= min(cnt - jk, n - cnt); i++) {
    //         res[jk + 2 * i - 1] = min(res[jk + 2 * i - 1], gg);
    //         res[jk + 2 * i] = min(res[jk + 2 * i], gg);
    //         gg++;
    //         cc = 2 * i + jk;
    //     }
    //     if (cnt - jk > n - cnt) {
    //         res[cc + 1] = min(res[cc + 1], gg);
    //     }
    // }
    // st.clear();
    for (int i = 0; i < n; i++) {
        int c = a[i].first;
        a[i].first = a[i].second, a[i].second = c;
    }
    sort(a.rbegin(), a.rend());
    cnt = 0;
    for (auto [r, l]: a) {
        cnt++;
        int jk = st.order_of_key(r) + 1;
        st.insert(l);
        //cout << r << ' ' << l << '\n';
        for (int i = 1; i <= jk; i++) {
            res[i] = 0;
        }
        int gg = 1, cc = 0;
        //cout << cnt - jk << ' ' << n - cnt << '\n';
        for (int i = 1; i <= min(cnt - jk, n - cnt); i++) {
            res[jk + 2 * i - 1] = min(res[jk + 2 * i - 1], gg);
            res[jk + 2 * i] = min(res[jk + 2 * i], gg);
            gg++;
            cc = 2 * i + jk;
        }
        if (cnt - jk > n - cnt) {
            res[cc + 1] = min(res[cc + 1], gg);
        }
    }
    while (q--) {
        int j;
        cin >> j;
        cout << res[j] << ' ';
    }
}