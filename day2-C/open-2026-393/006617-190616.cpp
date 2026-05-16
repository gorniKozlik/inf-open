#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
//
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <typename T>
// using ordered_multiset = tree<T, null_type, std::less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#pragma GCC optimize("unroll-loops", "O3")

using namespace std;

#define int long long
#define ff first
#define ss second
#define pb emplace_back
#define eb emplace
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define fora(i, n) for (int i = 0 ; i < n; i++)
#define forb(i, s, f) for (int i = s ; i < f; i++)
#define forc(i, n) for (int i = n - 1 ; i >= 0; i--)

using int128 = __int128_t;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using vvi = vector<vi>;

template<typename T>
using ve = vector<T>;
template<typename T>
using vve = ve<ve<T>>;

template<typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (auto &l : v)
        in >> l;
    return in;
}
template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto &l : v)
        out << l << ' ';
    out << '\n';
    return out;
}
template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& p) {
    in >> p.ff >> p.ss;
    return in;
}

template<typename T>
inline void amin(T& a, const T&b) {
    if (b < a)
        a = b;
}
template<typename T>
inline void amax(T& a, const T&b) {
    if (b > a)
        a = b;
}
constexpr long long INF = 1e18;
constexpr long long MOD = 998244353;


struct segtree {
    int n;
    vi tree;
    vi lazy;
    segtree(int N) : n(N), tree(4 * N, 0), lazy(4 * N, 0) {}
    void build (int i , int l, int r, const vi& a) {
        if (l + 1 == r) {
            if (l < sz(a))
                tree[i] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * i+ 1, l, m, a);
        build(2 * i+ 2, m, r, a);
        tree[i] = max(tree[2 * i+ 1], tree[2 * i+ 2]);
    }
    void build(const vi& a) {
        build(0, 0, n, a);
    }
    void push(int i) {
        if (lazy[i] != 0) {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
            tree[2 * i + 1] += lazy[i] ;
            tree[2 * i + 2] += lazy[i];
            lazy[i] = 0;
        }
    }

    void add(int i, int l, int r, int L, int R, int val) {
        if (r <= L || R <= l)
            return;
        if (L <= l && r <= R) {
            lazy[i] += val;
            tree[i] += val;
            return;
        }
        push(i);
        int m = (l + r) / 2;
        add(2 * i + 1, l, m, L, R ,val);
        add(2 * i+ 2, m, r, L, R, val);
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }
    void add(int L, int R, int val) {
        add(0, 0, n, L, R, val);
    }
    int get(int i, int l, int r, int L, int R) {
        if (r <= L || R <= l)
            return 0;
        if (L <= l && r <= R)
            return tree[i];
        push(i);
        int m = (l + r) / 2;
        return max(get(2 * i + 1, l, m, L, R), get(2 * i + 2, m, r, L, R));
    }
    int get(int L, int R) {
        return get(0, 0, n, L, R);
    }
    int get() {
        return tree[0];
    }
};

struct seg {
    int l, r, idx;
    seg(int a, int b, int c) : l(a), r(b), idx(c) {}
};

bool operator<(const seg& a, const seg& b) {
    return a.r < b.r;
}
struct Cmp {
    bool operator()(const seg& a, const seg& b) const {
        return a.l > b.l;
    }
};

void solve() {
    int n, q; cin >> n >> q;

    set<int> cords;
    ve<seg> segs;
    fora(i, n) {
        int l, r; cin >> l >> r;
        segs.pb(l,r, i);
        cords.eb(l);
        cords.eb(r);
    }

    int X = sz(cords);
    vi crd(all(cords));
    segtree tree(X);

    auto get = [&](int x) -> int{
        return lower_bound(all(crd), x) - crd.begin();
    };

    for (auto &[l, r, i] : segs) {
        int li = get(l);
        int ri = get(r);
        tree.add(li, ri + 1, 1);
    }
    
    set<seg> left(all(segs));
    set<seg, Cmp> right(all(segs));

    vi mp;
    mp.pb(tree.get());

    while (!left.empty()) {
        auto [l1, r1, i] = *left.begin();
        auto [l2, r2, j] = *right.begin();
        //cout << "(" << i << ' ' << j << ") ";
        if (i == j || r1 >= l2) {
            //cout << "del " << i << '\n';
            left.erase({l1, r1, i});
            right.erase({l1, r1, i});
            continue;
        }
        //cout<< "swap " << i << ' ' <<  j << '\n';
        tree.add(get(r1), get(l2) + 1, 1);
        tree.add(get(r1) + 1, get(l2), 1);
        mp.pb(tree.get());
        left.erase({l1, r1, i});
        right.erase({l1, r1, i});
        left.erase({l2, r2, j});
        right.erase({l2, r2, j});

        //seg seg1(l1, l2, i), seg2(r1, r2, j);
        //left.eb(seg1);
        //left.eb(seg2);
        //right.eb(seg1);
        //right.eb(seg2);
    }

    while (q--) {
        int k; cin >> k;
        int it = lower_bound(all(mp), k) - mp.begin();
        cout << it << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int itt = 1;
    //cin >>itt;
    while (itt--)
        solve();
    return 0;
}
