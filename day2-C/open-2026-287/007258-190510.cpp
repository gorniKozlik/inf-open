#define _GLIBCXX_DEBUG 1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #pragma GCC optimize("O3")
// #pragma GCC target("avx2,bmi,bmi2")
#define endl "\n"
#define all(x) x.begin(), x.end()
#define f first
#define s second
#define pb push_back
#define pop pop_back
#define wassert(x) if (!(x)) { cout << "pupupu"; exit(0); }

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

template <typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr ll INF = 1e9;
constexpr ll LINF = 1e18;
constexpr ld EPS = 1e-5;
constexpr ll MOD = 1e9 + 7, MOD2 = 998244353;

ll add(ll a, ll b, ll mod) {
    if (a + b >= mod) return a + b - mod;
    return a + b;
}

ll sub(ll a, ll b, ll mod) {
    if (a >= b) return a - b;
    return a - b + mod;
}

ll mul(ll a, ll b, ll mod) {
    return 1ll * a * b % mod;
}

ll binpow(ll a, ll b, ll mod) {
    if (b == 0) return 1;
    ll x = binpow(a, b / 2, mod);
    if (b % 2) return mul(x, mul(x, a, mod), mod);
    return mul(x, x, mod);
}

mt19937 rnd(1337228666);

struct seg {
    int l = 0, r = 0;
    seg() = default;
    seg(int l, int r) : l(l), r(r) {}
    bool operator==(seg o) const {
        return l == o.l && r == o.r;
    }
    bool in(seg o) const {
        return (r >= o.l && l <= o.r) || (l >= o.r && r <= o.l);
    }
};

bool comp(seg a, seg b) {
    return a.r < b.r;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector <seg> a(n);
    unordered_map<int, int> compress;
    vector <int> cords;
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        cords.push_back(a[i].l);
        cords.push_back(a[i].r);
    }
    sort(all(cords));
    cords.resize(unique(all(cords)) - cords.begin());
    for (auto el: cords) compress[el] = (int)compress.size();
    for (auto &el : a) {
        el.l = compress[el.l];
        el.r = compress[el.r];
    }
    sort(all(a), comp);

    int above = 0;
    auto get_cnt = [&] {
        deque <seg> st;
        int maxcnt = 0;
        for (int i = 0; i < a.size(); i++) {
            while (!st.empty() && a[i].l > st[0].r) st.pop_front();
            st.push_back(a[i]);
            maxcnt = max(maxcnt, (int)st.size());
        }
        return maxcnt;
    };
    vector <int> ans(n + 1, INF);
    auto setans = [&](int ops) {
        int x = get_cnt() + above;
        for (int i = 0; i <= x; i++) {
            ans[i] = min(ops, ans[i]);
        }
    };

    auto get_above = [&]() {
        int min_r = 0, max_l = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[min_r].r > a[i].r) min_r = i;
            if (a[max_l].l < a[i].l) max_l = i;
        }
        for (int i = 0; i < a.size(); i++) {
            if (a[i].l <= a[min_r].r && a[i].r >= a[max_l].l) return i;
        }
        return -1;
    };

    setans(0);
    int ops = 0;
    while (!a.empty()) {
        int x = get_above();
        if (x != -1) {
            a.erase(a.begin() + x);
            above++;
            continue;
        }

        int min_l = 0, max_r = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[min_l].l > a[i].l) min_l = i;
            if (a[max_r].r < a[i].r) max_r = i;
        }
        int l1 = a[min_l].l, r1 = a[min_l].r, l2 = a[max_r].l, r2 = a[max_r].r;
        wassert(min_l != max_r);
        a.erase(a.begin() + max(min_l, max_r));
        a.erase(a.begin() + min(min_l, max_r));
        above++;
        seg nw = {r1, l2};
        ops++;
        a.insert(lower_bound(all(a), nw, comp), nw);
        setans(ops);
    }

    int x;
    while (q--) {
        cin >> x;
        cout << ans[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while (t--) solve();
}