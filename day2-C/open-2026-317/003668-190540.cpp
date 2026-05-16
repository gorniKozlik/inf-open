
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//#pragma GCC optimize("O3,unroll_loops")
//#pragma GCC target("avx2")

#define int long long
using namespace  std;
using namespace __gnu_pbds;
int const INF = 1e18;

//tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
//----------------------------------------------------------------------------------------

int const maxn = 1e6;
int const LG = 23;


struct SegTree {
    int n;
    int h;
    vector<int> psh;
    vector<int> t;

    SegTree(int size){
        n = size;
        h = __lg(n);
        psh.assign(n, 0);
        t.assign(2 * n, 0);
    }

    void apply(int v, int val) {
        t[v] += val;
        if (v < n) psh[v] += val;
    }

    void push(int p) {
        for (int i = h; i >= 1; i--) {
            int c = p >> i;
            if (psh[c]) {
                apply(c << 1, psh[c]);
                apply(c << 1 | 1, psh[c]);
                psh[c] = 0;
            }
        }
    }

    void pull(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = max(t[p << 1], t[p << 1 | 1]) + psh[p];
        }
    }

    void upd(int l, int r, int val) {
        int ll = l + n;
        int rr = r + n;
        push(ll);
        push(rr - 1);
        for (; ll < rr; ll >>= 1, rr >>= 1) {
            if (ll & 1) apply(ll++, val);
            if (rr & 1) apply(--rr, val);
        }
        pull(l + n);
        pull(r + n - 1);
    }

    int get(int l, int r) {
        int res = 0;
        l += n;
        r += n;
        push(l);
        push(r - 1);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }


};


struct otr {
    int l;
    int r;
    int ind;
};

bool comp1(otr &l, otr &r) {
    return l.l > r.l;
}

bool comp2(otr &l, otr &r) {
    return l.r < r.r;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q, n;
    cin >> q >> n;
    vector<otr> t(n);
    vector<int> k;
    for (int i = 0; i < n; i++) {
        cin >> t[i].l >> t[i].r;
        t[i].ind = i;
        k.push_back(t[i].l);
        k.push_back(t[i].r);
    }
    sort(t.begin(), t.end(), comp1);
    deque<otr> ll;
    for (auto i: t) ll.push_back(i);
    sort(t.begin(), t.end(), comp2);
    deque<otr> rr;
    for (auto i: t) rr.push_back(i);
    sort(k.begin(), k.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < 2 * n; i++) mp[k[i]] = i;
    SegTree st(2 * n);
    vector<int> ans(n + 1, 0);
    vector<int> used(2 * n, 0);
    for (auto i: t) {
        st.upd(mp[i.l], mp[i.r] + 1, 1);
    }
    int p = st.get(0, 2 * n);
    int cnt = 1;
    while (p < n) {
        int l1, r1;
        int l2, r2;
        while (used[rr.front().ind]) rr.pop_front();
        l1 = rr.front().l;
        r1 = rr.front().r;
        used[rr.front().ind] = 1;
        while (used[ll.front().ind]) ll.pop_front();
        l2 = ll.front().l;
        r2 = ll.front().r;
        used[ll.front().ind] = 1;
        st.upd(mp[r1], mp[r1] + 1, 1);
        st.upd(mp[l2], mp[l2] + 1, 1);
        if (mp[l2] - mp[r1] > 1) {
            st.upd(mp[r1] + 1, mp[l2], 2);
        }
        int mx = st.get(0, 2 * n);
        for (int i = p + 1; i <= mx; i++) ans[i] = cnt;
        p = mx;
        cnt++;
    }
    while (q--) {
        int qq;
        cin >> qq;
        cout << ans[qq] << " ";
    }

    return 0;
}
