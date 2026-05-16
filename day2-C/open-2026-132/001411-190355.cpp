#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,popcnt")
#pragma GCC target("tune=native")

using namespace std;

#define int long long
#define sz(x) (int)x.size()
#define eb emplace_back
#define vi vector<int>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define vvi vector<vi>
#define vpi vector<pair<int, int> >
#define pi pair<int, int>
#define vvvi vector<vvi>

void solve_a() {
    int a, b; cin >> a >> b;
    cout << a + b << endl;
}

void solve_b() {

}

struct node {
    int mx, add;
};

struct segtree {
    vector<node> tree;
    int size;

    explicit segtree(int n): size(n) {
        tree.assign(4 * size, {0, 0});
    }

    void apply(int p, int x) {
        tree[p].mx += x;
        tree[p].add += x;
    }

    void push(int p) {
        apply(2 * p, tree[p].add);
        apply(2 * p + 1, tree[p].add);
        tree[p].add = 0;
    }

    void update(int lx, int rx, int x, int p, int l, int r) {
        //cout << l << ' ' << r << endl;
        if (l > rx || r < lx) return;
        if (lx <= l && r <= rx) {
            apply(p, x);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        update(lx, rx, x, 2 * p, l, m);
        update(lx, rx, x, 2 * p + 1, m + 1, r);
        tree[p].mx = max(tree[2 * p].mx, tree[2 * p + 1].mx);
    }

    void add(int lx, int rx, int x) {
        update(lx, rx, x, 1, 0, size - 1);
    }
};

void solve_c() {
    int n, q; cin >> n >> q;
    vpi v(n);
    vi ans(n, (int)9e18);
    set<int> st1;
    for (auto &[x, y] : v) {
        cin >> x >> y;
        st1.insert(x);
        st1.insert(y);
    }
    vi b(all(st1));
    for (auto &[x, y] : v) {
        x = lower_bound(all(b), x) - b.begin();
        y = lower_bound(all(b), y) - b.begin();
    }
    segtree st(2 * n);
    for (int i = 0; i < n; ++i) {
        st.add(v[i].fi, v[i].se, 1);
        //cout << v[i].fi << ' ' << v[i].se << endl;
    }
    int mx = st.tree[1].mx;
    for (int i = 0; i < mx; ++i) ans[i] = 0;
    set<pi> str, stl;
    for (int i = 0; i < n; ++i) {
        str.emplace(v[i].se, v[i].fi);
        stl.emplace(-v[i].fi, -v[i].se);
    }
    int c = 1;
    while (mx != n) {
        pi p1 = *str.begin();
        str.erase(str.begin());
        pi p2 = *stl.begin();
        stl.erase(stl.begin());
        swap(p1.fi, p1.se);
        p2.fi = abs(p2.fi);
        p2.se = abs(p2.se);
        if (p1 == p2) break;
        //cout << c << endl;
        st.add(p1.fi, p1.se, -1);
        st.add(p2.fi, p2.se, -1);
        st.add(p1.fi, p2.se, 1);
        st.add(p1.se, p2.fi, 1);
        for (int i = mx; i < st.tree[1].mx; ++i) ans[i] = c;
        c++;
        mx = st.tree[1].mx;
        //cout << c << ' ' << mx << endl;
    }
    // << 1 << endl;
    while (q--) {
        int k; cin >> k;
        cout << ans[--k] << ' ';
    }
    cout << endl;
}

void solve_d() {

}

signed main() {
   //freopen("C:/work/untitled1/input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) solve_c();
}