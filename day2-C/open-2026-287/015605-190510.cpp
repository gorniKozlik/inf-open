// #define _GLIBCXX_DEBUG 1
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

int get_max(const vector <seg>& a) {
    deque <seg> st;
    int maxcnt = 0;
    for (int i = 0; i < a.size(); i++) {
        while (!st.empty() && a[i].l > st[0].r) st.pop_front();
        st.push_back(a[i]);
        if (maxcnt < st.size()) {
            maxcnt = st.size();
        }
    }
    return maxcnt;
}

void change(vector <seg> &a, int i1, int i2, int type) {
    int l1 = a[i1].l, r1 = a[i1].r, l2 = a[i2].l, r2 = a[i2].r;
    a.erase(a.begin() + max(i1, i2));
    a.erase(a.begin() + min(i1, i2));
    seg nw1, nw2;
    if (type == 1) {
        nw1 = {min(l1, r2), max(l1, r2)};
        nw2 = {min(l2, r1), max(l2, r1)};
    } else {
        nw1 = {min(l1, l2), max(l1, l2)};
        nw2 = {min(r1, r2), max(r1, r2)};
    }
    a.insert(lower_bound(all(a), nw1, comp), nw1);
    a.insert(lower_bound(all(a), nw2, comp), nw2);
}

bool rec(int ops, int goal, vector <seg> &a) {
    vector <seg> a_cpy = a;
    if (ops == 0) return get_max(a) >= goal;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            for (int type = 1; type <= 2; type++) {
                change(a, i, j, type);
                bool res = rec(ops - 1, goal, a);
                a = a_cpy;
                if (res) return true;
            }
        }
    }
    return false;
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
    vector <int> ans(n + 1);
    int last_ans = 1;
    for (int i = 0; i <= n / 2; i++) {
        while (rec(i, last_ans, a)) {
            ans[last_ans] = i;
            last_ans++;
        }
    }

    int x;
    for (int i = 0; i < q; i++) {
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