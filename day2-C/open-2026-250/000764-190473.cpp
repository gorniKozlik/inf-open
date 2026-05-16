#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x) x.begin(), x.end()
#define len(x) (int)x.size()
#define start auto st = clock()
#define finish auto fin = clock(); cerr << 1000 * (fin - st) / (ld)CLOCKS_PER_SEC << endl
const ll mod2 = 998244353;

using namespace std;

// #define mtask
// #define int ll

struct tree {

    int n;
    vector<int> t;
    vector<int> add;

    tree(int n_) {
        n = n_;
        t.resize(4 * n);
        add.resize(4 * n);
    }

    void push(int v) {
        t[2 * v + 1] += add[v];
        t[2 * v + 2] += add[v];
        add[2 * v + 1] += add[v];
        add[2 * v + 2] += add[v];
        add[v] = 0;
    }

    void upd(int v, int vl, int vr, int ql, int qr, int x) {
        if (qr <= vl || vr <= ql) return;
        if (ql <= vl && vr <= qr) {
            add[v] += x;
            t[v] += x;
            return;
        }
        push(v);
        int mid = (vl + vr) / 2;
        upd(2 * v + 1, vl, mid, ql, qr, x);
        upd(2 * v + 2, mid, vr, ql, qr, x);
        t[v] = max(t[2 * v + 1], t[2 * v + 2]);
    }

    void upd(int l, int r, int x) {
        upd(0, 0, n, l, r, x);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    {

        vector<int> tt;
        for (int i = 0; i < n; ++i) {
            cin >> a[i].first >> a[i].second;
            tt.push_back(a[i].first);
            tt.push_back(a[i].second);
        }
        sort(all(tt));
        tt.resize(unique(all(tt)) - tt.begin());
        map<int, int> mp;
        for (int i = 0; i < len(tt); ++i) {
            mp[tt[i]] = i;
        }
        for (auto &[x, y] : a) {
            x = mp[x];
            y = mp[y];
        }
    }
    sort(all(a));
    tree t(2 * n);
    set<pair<int, int>> lb, rb;
    for (int i = 0; i < n; ++i) {
        lb.insert({a[i].first, i});
        rb.insert({a[i].second, i});
    }
    for (auto [x, y] : a) {
        t.upd(x, y + 1, 1);
    }
    vector<int> ans(n + 1);

    auto del = [&](int i) {
        lb.erase({a[i].first, i});
        rb.erase({a[i].second, i});
        t.upd(a[i].first, a[i].second + 1, -1);
    };

    auto ins = [&](int i) {
        lb.insert({a[i].first, i});
        rb.insert({a[i].second, i});
        t.upd(a[i].first, a[i].second + 1, 1);
    };


    int ptr = t.t[0] + 1;
    int cnt = 0;
    while (true) {
        auto [l, i] = *lb.rbegin();
        auto [r, j] = *rb.begin();
        if (l <= r) break;
        del(i);
        del(j);
        swap(a[i].first, a[j].second);
        ins(i);
        ins(j);
        ++cnt;
        while (ptr <= t.t[0]) {
            ans[ptr] = cnt;
            ++ptr;
        }
    }

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
#ifdef mtask
    int t;
    cin >> t;
    while (t--)
#endif
        solve();
}