#include<bits/stdc++.h>
using namespace std;

struct Node{
    int mx, p;
};

Node mrg(const Node &a, const Node &b) {
    return {max(a.mx, b.mx), 0};
}

struct segtree{
    int sz;
    vector<Node> t;

    void push(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        int v = t[x].p;
        t[2 * x + 1].mx += v;
        t[2 * x + 1].p += v;
        t[2 * x + 2].mx += v;
        t[2 * x + 2].p += v;
        t[x].p = 0;
    }

    void init(int n) {
        sz = n;
        t.assign(4 * n - 1, {0, 0});
    }

    void upd(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) return;
        if (l <= lx && rx <= r) {
            t[x].mx += v;
            t[x].p += v;
            return;
        }
        push(x, lx, rx);
        int mid = (lx + rx) / 2;
        upd(l, r, v, 2 * x + 1, lx, mid);
        upd(l, r, v, 2 * x + 2, mid, rx);
        t[x] = mrg(t[2 * x + 1], t[2 * x + 2]);
    }

    void upd(int l, int r, int v) {
        upd(l, r, v, 0, 0, sz);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    vector<array<int, 2>> a;
    vector<int> as, ans(n + 1, -1);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        as.push_back(l);
        as.push_back(r);
        a.push_back({l, r});
    }
    sort(as.begin(), as.end());
    for (int i = 0; i < 2 * n; i++) {
        mp[as[i]] = i;
    }
    segtree st;
    st.init(2 * n);
    for (int i = 0; i < n; i++) {
        a[i] = {mp[a[i][0]], mp[a[i][1]]};
        st.upd(a[i][0], a[i][1] + 1, 1);
    }
    vector<array<int, 2>> al = a, ar;
    for (auto [l, r] : a) {
        ar.push_back({r, l});
    }
    sort(al.rbegin(), al.rend());
    sort(ar.begin(), ar.end());
    int i = 1;
    int res1 = st.t[0].mx;
    while (i <= res1) {
        ans[i] = 0;
        i++;
    }
    for (int k = 0; k < n; k++) {
        if (ar[k][0] > al[k][0]) continue;
        int l1 = ar[k][1], r1 = ar[k][0], l2 = al[k][0], r2 = al[k][1];
        st.upd(l1, r1 + 1, -1);
        st.upd(l2, r2 + 1, -1);
        swap(l2, r1);
        st.upd(l1, r1 + 1, 1);
        st.upd(l2, r2 + 1, 1);
        int res = st.t[0].mx;
        while (i <= res) {
            ans[i] = k + 1;
            i++;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int32_t main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    solve();
}
