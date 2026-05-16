#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

//#define int long long

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
//#define endl "\n"

template<class T>
istream& operator >> (istream& in, pair<T, T>& a) {
    in >> a.first >> a.second;
    return in;
}
template<class T>
istream& operator >> (istream& in, vector<T>& a) {
    for (T& x : a){
        in >> x;
    }
    return in;
}
template<class T>
ostream& operator << (ostream& out, pair<T, T> a) {
    out << a.first << " " << a.second << " ";
    return out;
}
template<class T>
ostream& operator << (ostream& out, vector<T> a) {
    for (auto& x : a) {
        out << x << " ";
    }
    return out;
}
#define debug(x) cout << (#x) << ": " << (x) << endl

constexpr int inf = 1e9 + 1;
constexpr ll INF = 1e18 + 1;

vi solve3(int n, vi& qq) {
    vi ans(n);
    for (int i = 1; i < n; i++) {
        ans[i] = (i + 1) / 2;
    }
    vi vec;
    for (auto x : qq) {
        vec.push_back(ans[x - 1]);
    }
    return vec;
}


struct SGT {
    int n;
    vi tree, d;

    SGT(int n_) {
        n = n_;
        tree.assign(4 * n, 0);
        d.assign(4 * n, 0);
    }

    void push(int v) {
        if (d[v] == 0) return;
        tree[v * 2 + 1] += d[v];
        d[v * 2 + 1] += d[v];
        tree[v * 2 + 2] += d[v];
        d[v * 2 + 2] += d[v];
        d[v] = 0;
    }
    void upd(int v, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            tree[v] += val;
            d[v] += val;
            return;
        }
        if (qr <= l || r <= ql) {
            return;
        }

        push(v);
        int m = (l + r) / 2;
        upd(v * 2 + 1, l, m, ql, qr, val);
        upd(v * 2 + 2, m, r, ql, qr, val);
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
    void upd(int ql, int qr, int val) {
        if (ql >= qr) return;
        upd(0, 0, n, ql, qr, val);
    }

    int get(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        if (qr <= l || r <= ql) {
            return 0;
        }

        push(v);
        int m = (l + r) / 2;
        return max(get(v * 2 + 1, l, m, ql, qr), get(v * 2 + 2, m, r, ql, qr));
    }
    int get(int ql, int qr) {
        return get(0, 0, n, ql, qr);
    }

    int get() {
        return tree[0];
    }
};

void compress(vi& a) {
    vi a0 = a;
    sort(all(a0));
    a0.erase(unique(all(a0)), a0.end());

    for (auto& x : a) {
        x = lower_bound(all(a0), x) - a0.begin();
    }
}

void upd(int l, int r, int val, vi& cnt) {
    for (int i = l; i <= r; i++) {
        cnt[i] += val;
    }
}
int get(vi& cnt) {
    return *max_element(all(cnt));
}

vi fast(int n, int q, vector<pi> segs, vi& qq) {
    vi a;
    for (auto [l, r] : segs) {
        a.push_back(l);
        a.push_back(r);
    }
    compress(a);
    for (int i = 0; i < 2 * n; i += 2) {
        segs[i / 2] = {a[i], a[i + 1]};
    }

    sort(all(a));
    pi mid_seg = {a[n - 1], a[n]};

    multiset<pi> left, right;
    SGT tree(n * 2);
    for (auto [l, r] : segs) {
        if (r <= mid_seg.first) {
            left.insert({r, l});
        }
        if (mid_seg.second <= l) {
            right.insert({l, r});
        }

        //upd(l, r, 1, cnt);
        tree.upd(l, r + 1, 1);
    }

    vi ans(n + 1);
    int mx = tree.get();
    for (int i = 0; i <= mx; i++) {
        ans[i] = 0;
    }

    int cur = 0;
    while (!left.empty()) {
        auto [r1, l1] = *left.begin();
        left.erase(left.begin());
        auto [l2, r2] = *--right.end();
        right.erase(--right.end());

        tree.upd(l1, r1 + 1, -1);

        tree.upd(l2, r2 + 1, -1);

        tree.upd(l1, r2 + 1, 1);

        tree.upd(r1, l2 + 1, 1);
        cur++;

        int mx0 = mx;
        mx = tree.get();
        for (int i = mx0 + 1; i <= mx; i++) {
            ans[i] = cur;
        }
    }

    vi res;
    for (auto x : qq) {
        res.push_back(ans[x]);
    }

    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<pi> segs(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
    }
    vi qq(q); cin >> qq;

    if (true) {
        cout << fast(n, q, segs, qq) << endl;
        return;
    }


    sort(all(segs));
    bool flag3 = true;
    for (int i = 1; i < n; i++) {
        if (segs[i - 1].second >= segs[i].first) {
            flag3 = false;
        }
    }
    if (flag3) {
        cout << solve3(n, qq) << endl;
        return;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
