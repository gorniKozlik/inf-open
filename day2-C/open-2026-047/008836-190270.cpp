// #pragma GCC optimize("O3,fast-math,unroll-loops")
#include <bits/stdc++.h>

#define i64 int64_t
#define vi vector<int>
#define vvi vector<vi>
#define vc vector
#define vb vc<bool>
#define pb push_back
#define pii pair<int, int>
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

using namespace std;

template <typename T>

istream& operator>>(istream& in, vector<T> &a) {
    for (T &el : a) in >> el;
    return in;
}

template <typename T>

ostream& operator<<(ostream& out, vector<T> a) {
    for (T &el : a) out << el << " ";
    return out;
}

struct node_t {
    int start, end;
    int mx= -1e9;

    node_t *left, *right;

    node_t (int start_, int end_) {
        start = start_;
        end = end_;
        if (end != start + 1) {
            int mid = (start + end) / 2;
            left = new node_t(start, mid);
            right = new node_t(mid, end);
        }
    }

    void upd(int l, int r, int x) {
        if (l <= start && r >= end) {
            mx = max(mx, x);
            return;
        }
        if (l >= end || r <= start) return;
        left->upd(l, r, x);
        right->upd(l, r, x);
    }

    int get(int i) {
        if (end == start + 1) return mx;
        if (i < (start + end) / 2) return max(mx, left->get(i));
        return max(mx, right->get(i));
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vc<pii> p(n);
    vi a;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].fi >> p[i].se;
        a.pb(p[i].fi);
        a.pb(p[i].se);
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    for (int i = 0; i < n; ++i) {
        p[i].fi = lower_bound(all(a), p[i].fi) - a.begin();
        p[i].se = lower_bound(all(a), p[i].se) - a.begin();
    }
    int mx = 0;
    node_t ans(0, n + 1);
    vi add(2 * n + 1);
    vi del(2 * n);
    for (int i = 0; i < n; ++i) {
        ++add[p[i].se + 1];
        ++del[p[i].fi];
    }
    int cnt_r = n;
    int cnt_l = 0;
    vb is(2 * n + 1);
    for (int i = 0; i < n; ++i) {
        is[p[i].fi] = 1;
        is[p[i].se] = 0;
    }
    for (int i = 0; i < a.size(); ++i) {
        cnt_l += add[i];
        cnt_r -= del[i];
        int cnt = n - cnt_l - cnt_r;
        int l = cnt;
        int r = cnt + min(cnt_l, cnt_r) * 2;
        if (cnt_l > cnt_r && is[i]) ++r;
        else if (cnt_l < cnt_r && !is[i]) ++r;
        ans.upd(l, r + 1, l);
        mx = max(mx, l);
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= mx) cout << 0 << ' ';
        else {
            cout << (k - ans.get(k) + 1) / 2 << ' ';
            
        }
    }
}

int32_t main() {
    // freopen("inputa.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}