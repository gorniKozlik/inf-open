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
        return (r > o.l && l < o.r) || (l > o.r && r < o.l);
    }
};

class comp1{
public:
    bool operator()(const seg& a, const seg& b) const {
        return a.l < b.l;
    }
};

class comp2{
public:
    bool operator()(const seg& a, const seg& b) const {
        return a.r > b.r;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector <seg> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].l >> a[i].r;
    // я должен уметь быстро находить отрезок с наименьшим l, с наибольшим r и удалять за быстро и добавлять за быстро
    // ...а ещё надо уметь быстро посчитать клики в самом начале, это тоже та ещё эпопея
    auto b = a;
    sort(all(a), comp1());
    sort(all(b), comp2());
    reverse(all(b));
    int cnt = 1, maxcnt = 1, cur_last = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].in(b[cur_last])) {
            cnt++;
            maxcnt = max(maxcnt, cnt);
        } else {
            while (!a[i].in(b[cur_last])) {
                cur_last++;
                cnt--;
            }
            if (cur_last == i) cnt++;
        }
    }
    maxcnt = max(maxcnt, cnt);
    vector <int> ans(n + 2);
    for (int i = 0; i <= maxcnt; i++) ans[i] = 0;

    // отрезок с наименьшим l щас найти очень легко, проблема лишь в том, что мы ещё ведь и добавить должны
    // можно сделать пару сетов, искать в обоих сетах начала, а после удалять, ища нужные отрезки (уникальность колышек)
    // ну звучит как план

    set <seg, comp1> s1;
    set <seg, comp2> s2;
    for (auto el: a) {
        s1.insert(el);
        s2.insert(el);
    }

    auto check_all_above = [&]() { // ооооочень плохо
        auto it = s1.begin();
        auto rfirst = *--s2.end();
        auto llast = *--s1.end();
        for (; it != s1.lower_bound(rfirst); ++it) {
            if (it->r > llast.l) {
                return it;
            }
        }
        return s1.end();
    };
    cnt = maxcnt;
    int ops = 0;
    while (cnt <= n) {
        if (s1.empty() || s2.empty()) break;
        auto it1 = s1.begin();
        auto it2 = s2.begin();
        auto it = check_all_above();
        if (it != s1.end()) {
            if (ops) {
                cnt++;
                ans[cnt] = ops;
            }
            s2.erase(*it);
            s1.erase(it);
            continue;
        }

        // хотим переподвесить один на весь отрезок, другой как получится
        int l1 = it1->l, r1 = it1->r, l2 = it2->l, r2 = it2->r;
        s1.erase(s1.begin());
        s1.erase(s1.lower_bound({l2, r2}));
        s2.erase(s2.begin());
        s2.erase(s2.lower_bound({l1, r1}));
        cnt++;
        ops++;
        s1.insert({r1, l2});
        s2.insert({r1, l2});
        ans[cnt] = ops;
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