#pragma GCC optimize("Ofast")
#pragma GCC target("avx2", "bmi2", "popcnt", "lzcnt")
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <climits>
#include <queue>
#include <random>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace __gnu_pbds;

typedef long long int lint;
typedef long double ld;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ost;

constexpr int LOG = 20;
constexpr int MOD = 998244353;
constexpr lint INF = 8e18 + 7;

inline void preset() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
}

#define vl (2 * v + 1)
#define vr (2 * v + 2)
struct SegTree {
    vector <lint> t;
    vector <lint> lazy;
    int n;
    SegTree (int n = 0): n(n), t(4 * n, 0), lazy(4 * n, 0) {}
    void push(int v, int L, int R) {
        if (!lazy[v]) return;
        t[v] += lazy[v];
        if (R - L != 1) {
            lazy[vl] += lazy[v];
            lazy[vr] += lazy[v];
        }
        lazy[v] = 0;
    }
    void build(int v, int L, int R, vector <int> &a) {
        if (R - L == 1) {
            t[v] = a[L];
            return;
        }
        int M = (L + R) / 2;
        build(vl, L, M, a);
        build(vr, M, R, a);
        t[v] = max(t[vl], t[vr]);
    }
    void upd(int v, int L, int R, int i, lint x) {
        push(v, L, R);
        if (R - L == 1) {
            t[v] += x;
            return;
        }
        int M = (L + R) / 2;
        if (i >= M) upd(vr, M, R, i, x);
        else upd(vl, L, M, i, x);
        t[v] = max(t[vl], t[vr]);
    }
    void upd(int v, int L, int R, int l, int r, lint x) {
        if (l >= R || L >= r) return;
        push(v, L, R);
        if (l <= L && R <= r) {
            lazy[v] += x;
            push(v, L, R);
            return;
        }
        int M = (L + R) / 2;
        upd(vl, L, M, l, r, x);
        upd(vr, M, R, l, r, x);
        t[v] = max(t[vl], t[vr]);
    }
    int get(int v, int L, int R, int l, int r) {
        if (l >= R || L >= r) return 0;
        push(v, L, R);
        if (l <= L && R <= r) {
            return t[v];;
        }
        int M = (L + R) / 2;
        return max(get(vl, L, M, l, r), get(vr, M, R, l, r));
    }
    int get() {
        return get(0, 0, n, 0, n);
    }
};

struct _Fenwick {
    vector <lint> t;
    int n;
    _Fenwick(const int n = 0): n(n), t(n + 1, 0) {}
    _Fenwick(const vector <lint> &a): n((int) a.size()), t(a.size() + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
    void upd(int pos, lint val) {
        for (;pos <= n; pos += pos & -pos) t[pos] += val;
    }
    lint sum(int r) {
        lint s = 0;
        for (; r > 0; r-= r& -r) s += t[r];
        return s;
    }
    lint rsq(int l, int r) {
        return sum(r) - sum(l);
    }
};

struct Fenwick {
    _Fenwick d, di;
    int n;
    Fenwick(int n = 0): n(n), d(n), di(n) {}
    Fenwick(const vector <int> &a): n((int) a.size()) {
        vector <lint> D(n), Di(n);
        D[0] = a[0];
        for (int i = 1; i < n; ++i) D[i] = a[i] - a[i - 1];
        for (int i = 0; i < n; ++i) Di[i] = D[i] * (i + 1);
        d = _Fenwick(D);
        di = _Fenwick(Di);
    }
    void _upd(int pos, lint val) {
        d.upd(pos, val);
        di.upd(pos, val * pos);
    }
    void upd(int l, int r, lint x) {
        if (r <= l) return;
        _upd(l + 1, x);
        if (r < n) _upd(r + 1, -x);
    }
    lint _sum(int r) {
        return (r + 1) * d.sum(r) - di.sum(r);
    }
    lint rsq(int l, int r) {
        return _sum(r) - _sum(l);
    }
};

vector <pair<int, int>> shrink(const vector<pair<int, int>> &a) {
    int n = a.size();
    vector <pair<int, int>> b (2 * a.size());
    for (int i = 0; i < n; ++i) {
        b[2 * i] = make_pair(a[i].first, 2 * i);
        b[2 * i + 1] = make_pair(a[i].second, 2 * i + 1);
    }
    sort(b.begin(), b.end());
    vector<pair<int, int>> res(a.size());
    for (int i = 0; i < 2 * n; ++i) {
        auto [el, j2] = b[i];
        int j = j2 / 2;
        if (j2 & 1) res[j].second = i;
        else res[j].first = i;
    }
    return res;
}

int main() {
    preset();
    int n, q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto &[l, r]: a) cin >> l >> r;
    a = shrink(a);
    vector <int> cnt(2 * n, 0);
    vector <pair<int, int>> scanline;
    for (auto &el: a) {
        scanline.emplace_back(el.first, 1);
        scanline.emplace_back(el.second, -1);
    }

    sort(scanline.begin(), scanline.end());
    int c = 0;
    for (auto &[x, delta]: scanline) {
        if (delta == 1) ++c;
        cnt[x] = c;
        if (delta == -1) --c;
    }
    int k = 2 * n;
    SegTree t(k); t.build(0, 0, k, cnt);
    // for (int j = 0; j < k; ++j) cout << t.get(0, 0, k, j, j + 1) << " "; cout << endl;
    // vector <int> rs, ls;
    set<int> rs;
    set<int, greater<>> ls;
    for (auto &[l, r]: a) {
        // rs.push_back(r);
        // ls.push_back(l);
        ls.insert(l);
        rs.insert(r);
    }
    // for (auto [l, r]: a) cout << l << " " << r << endl;
    // sort(ls.begin(), ls.end()); reverse(ls.begin(), ls.end());
    // sort(rs.begin(), rs.end());
    int mx = *max_element(cnt.begin(), cnt.end());
    vector <int> ans(n + 1);
    for (int i = 0; i <= mx; ++i) ans[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (mx >= n) break;
        // int r = ls[i];
        // int l = rs[i];
        int r = *ls.begin(); ls.erase(ls.begin());
        int l = *rs.begin(); rs.erase(rs.begin());
        if (r < l) break;
        rs.insert(r);
        ls.insert(l);
        // cout << l << " " << r << "\n";
        t.upd(0, 0, k, l, 1);
        t.upd(0, 0, k, r, 1);
        if (r - (l + 1) >= 1) t.upd(0, 0, k, l + 1, r, 2);
        // for (int j = 0; j < k; ++j) cout << t.get(0, 0, k, j, j + 1) << " "; cout << endl;
        int nmx = t.get();
        for (int j = mx + 1; j <= nmx; ++j) ans[j] = i + 1;
        mx = nmx;
        // cout << i + 1 << " " << mx << endl;
    }
    // for (auto el: ans) cout << el << " ";
    while (q--) {
        int x; cin >> x;
        cout << ans[x] << " ";
    }
    return 0;
}