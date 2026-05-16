#include <bits/stdc++.h>

// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2")

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128_t;

istream& operator>>(istream& is, i128 &x) {
    long long a;
    is >> a;
    x = (i128) a;
    return is;
}
ostream& operator<<(ostream& os, i128 &x) {
    long long a = (long long) x;
    os << a;
    return os;
}

const ll inf = 1e18 + 1e16;
const ll inf_t = 1e9 + 7;
const ll mod = 998244353;

#define int ll

struct SegmentTree {
    struct Node {
        int x = 0;
        int add = 0;

        Node() = default;
        Node(int x, int add): x(x), add(add) {}
    };

    int n;
    vector <Node> t;

    SegmentTree() = default;
    SegmentTree(int n): n(n) {
        t.resize(4 * n);
    }

    void apply(int v, int x) {
        t[v].x = x;
        t[v].add = x;
    }

    void push(int v) {
        if (t[v].add == 0) return;
        apply(2 * v + 1, t[v].add);
        apply(2 * v + 2, t[v].add);

        t[v].add = 0;
    }

    void update(int v, int l, int r, int lq, int rq, int x) {
        if (lq <= l && r <= rq) {
            apply(v, x);
            return;
        }
        if (rq <= l || r <= lq) return;

        int m = (l + r) / 2;
        push(v);
        update(2 * v + 1, l, m, lq, rq, x);
        update(2 * v + 2, m, r, lq, rq, x);

        t[v].x = max(t[2 * v + 1].x, t[2 * v + 2].x);
    }
    void update(int l, int r, int x) {
        update(0, 0, n, l, r, x);
    }

    void get(int v, int l, int r, vector <int> &a) {
        if (r - l == 1) {
            a[l] = t[v].x;
            return;
        }
        int m = (l + r) / 2;
        push(v);
        get(2 * v + 1, l, m, a);
        get(2 * v + 2, m, r, a);
    }
    void get(vector <int> &a) {
        get(0, 0, n, a);
    }
};

struct quest {
    int x;
    int t;

    quest() = default;
    quest(int x, int t): x(x), t(t) {}

    bool operator<(const quest &oth) const {
        return make_pair(x, -t) < make_pair(oth.x, -oth.t);
    }
};

struct lquest {
    int t;
    int l, r;
    int x;

    lquest() = default;
    lquest(int t, int l, int r, int x): t(t), l(l), r(r), x(x) {}

    bool operator<(const lquest& oth) const {
        return x < oth.x;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;

    int bal = 0;
    int mx_bal = 0;

    vector <quest> qs;
    for (int i = 0; i < n; ++i) {
        qs.push_back(quest(a[i].first, 1));
        qs.push_back(quest(a[i].second, -1));
    }

    sort(qs.begin(), qs.end());
    vector <int> ans(n + 1, n / 2);
    ans[0] = 0;
    int lt = 0;
    int rt = 0;
    SegmentTree t1(n + 1);
    SegmentTree t2(n + 1);
    SegmentTree t3(n + 1);

    t1.update(0, n + 1, inf_t);

    vector <lquest> upd;
    for (int i = 0; i < qs.size(); ++i) {
        if (qs[i].t == 1) {
            ++lt;
        } else {
            ++rt;
        }
        bal += qs[i].t;
        mx_bal = max(mx_bal, bal);

        if (qs[i].t == 1) continue;

        ++bal;
        int lft = rt - 1;
        int rht = n - lt;

        int add = 2 * min(lft, rht);
        // for (int j = 1; j <= bal; ++j) {
        //     ans[j] = 0;
        // }
        t1.update(0, bal + 1, 0);
        // for (int j = bal + 1; j <= bal + add; ++j) {
        //     ans[j] = min(ans[j], (j - bal + 1) / 2);
        // }
        upd.push_back(lquest(2, bal + 1, bal + add + 1, bal));
        
        int ans_cur = add / 2;
        // for (int j = bal + add + 1; j <= n; ++j) {
        //     ans[j] = min(ans[j], j - bal - add + ans_cur);
        // }
        upd.push_back(lquest(3, bal + add + 1, n + 1, bal + add - ans_cur));
        --bal;
    }

    sort(upd.begin(), upd.end());
    for (int i = 0; i < upd.size(); ++i) {
        if (upd[i].t == 2) {
            t2.update(upd[i].l, upd[i].r, upd[i].x);
        } else {
            t3.update(upd[i].l, upd[i].r, upd[i].x);
        }
    }

    vector <int> ft1(n + 1);
    vector <int> ft2(n + 1);
    vector <int> ft3(n + 1);

    t1.get(ft1);
    t2.get(ft2);
    t3.get(ft3);

    while (q--) {
        int k;
        cin >> k;
        cout << min({ft1[k], k - ft2[k], k - ft3[k], k / 2}) << " ";
    }
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}

// nu i kak pisat' eto vashe STB ?