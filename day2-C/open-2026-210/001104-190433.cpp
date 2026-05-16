#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

const ll INF = 2e18;
const ll MOD = 1e9 + 7;
const ll mod = 998244353;

using namespace std;

struct Node {
    bool fl;
    ll x, add;
    Node() {
        fl = 0;
        x = 0;
        add = 0;
    }
};

struct segtree {
    vector<Node> tree;
    int sz;

    Node merge(Node a, Node b) {
        if (!a.fl) {
            return b;
        }
        if (!b.fl) {
            return a;
        }
        Node x;
        x.fl = 1;
        x.x = max(a.x, b.x);
        return x;
    }

    Node base(int x) {
        Node a;
        a.fl = 1;
        a.x = x;
        return a;
    }

    void build(int v, int l, int r, vector<int>& a) {
        if (l + 1 == r) {
            tree[v] = base(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * v + 1, l, mid, a);
        build(2 * v + 2, mid, r, a);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void bld(vector<int>& a) {
        sz = a.size();
        tree.assign(4 * sz, Node());
        build(0, 0, sz, a);
    }

    segtree(vector<int>& a) {
        bld(a);
    }

    void push(int v, int l, int r) {
        ll x = tree[v].add;
        if (x == 0) {
            return;
        }
        tree[v].add = 0;
        tree[v].x += x;
        if (2 * v + 2 >= tree.size()) {
            return;
        }
        tree[2 * v + 1].add += x;
        tree[2 * v + 2].add += x;
    }

    void edit(int v, int l, int r, int lx, int rx, int x) {
        push(v, l, r);
        if (l >= lx && r <= rx) {
            tree[v].add += x;
            push(v, l, r);
            return;
        }
        if (r <= lx || l >= rx) {
            return;
        }
        int mid = (l + r) / 2;
        edit(2 * v + 1, l, mid, lx, rx, x);
        edit(2 * v + 2, mid, r, lx, rx, x);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void add(int l, int r, int x) {
        edit(0, 0, sz, l, r, x);
    }

    Node get(int v, int l, int r, int lq, int rq) {
        push(v, l, r);
        if (l >= rq || r <= lq) {
            return Node();
        }
        if (l >= lq && r <= rq) {
            return tree[v];
        }
        int mid = (l + r) / 2;
        return merge(get(2 * v + 1, l, mid, lq, rq), get(2 * v + 2, mid, r, lq, rq));
    }

    Node get(int l, int r) {
        return get(0, 0, sz, l, r);
    }
};

struct seg {
    int l, r, ind;
};

bool cmpl(seg a, seg b) {
    return a.l > b.l;
}

bool cmpr(seg a, seg b) {
    return a.r < b.r;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    vector<int> v(2 * n);
    segtree st(v);
    v = l;
    for (auto x : r) {
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        l[i] = lower_bound(v.begin(), v.end(), l[i]) - v.begin();
        r[i] = lower_bound(v.begin(), v.end(), r[i]) - v.begin();
        st.add(l[i], r[i] + 1, 1);
    }
    vector<seg> left, right;
    for (int i = 0; i < n; i++) {
        left.push_back({l[i], r[i], i});
    }
    right = left;
    sort(right.begin(), right.end(), cmpl);
    sort(left.begin(), left.end(), cmpr);
    int ind = 0;
    vector<int> ans(n + 1);
    int mx = st.get(0, 2 * n).x;
    for (int i = 0; i < n; i++) {
        while (ind <= mx) {
            ans[ind] = i;
            ind++;
        }
        seg L = left[i];
        seg R = right[i];
        if (L.r > R.l) {
            break;
        }
        st.add(L.r, R.l, 1);
        st.add(L.r + 1, R.l + 1, 1);
        mx = st.get(0, 2 * n).x;
    }
    while (ind <= n) {
        ans[ind] = n;
        ind++;
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    bool MULTITEST = 0;
    #ifdef egg
        MULTITEST = 1;
        freopen("test.txt", "r", stdin);
    #endif
    if (MULTITEST) {
        cin >> t;
    }
    while (t--) {
        solve();
    }
    return 0;
}
