// Увидеть мир в одной песчинке
// И Космос весь в лесной травинке,
// Вместить в ладони бесконечность
// И в миге мимолетном вечность.

// Узнать об истинности лжи,
// Не поняв смысла, жизнь прожить,
// Принять рождение и смерть,
// И, улыбаясь, умереть.

// В минуту гнева и сомнений
// Иль в испытаниях больших
// Не верных не прими решений
// И делать вывод не спеши

// В период козней злого рока,
// В миг расставаний, в час рук
// Не падай духом раньше срока,
// Не опускай в бессилье рук.

#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <chrono>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
// using int128 = __int128_t;
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll MOD = 1e9 + 7;
struct mint {
    ll num;
    mint(ll _num) : num(_num) {}
    mint operator+(mint y) {
        if (num + y.num >= MOD) return num + y.num - MOD;
        return num + y.num;
    }
    mint operator-(mint y) {
        if (num - y.num < 0) return num - y.num + MOD;
        return num - y.num;
    }
    mint operator*(mint y) {
        return num * y.num % MOD;
    }
    mint pow(int n) {
        mint res = 1;
        mint a = *this;
        for (int i = 0; (1ll << i) <= n; ++i, a = a * a) {
            if ((n >> i) & 1) res = res * a;
        }
        return res;
    }
    mint inv() {
        return (*this).pow(MOD - 2);
    }
    mint operator/(mint y) {
        return num * y.inv().num % MOD;
    }
    void operator+=(mint y) {
        num = (*this + y).num;
    }
    void operator-=(mint y) {
        num = (*this - y).num;
    }
    void operator*=(mint y) {
        num = (*this * y).num;
    }
    void operator/=(mint y) {
        num = (*this / y).num;
    }
};
istream& operator>>(istream &in, mint &x) {
    in >> x.num;
    return in;
}
ostream& operator<<(ostream &out, mint &x) {
    out << x.num;
    return out;
}
ll INF = 1e18;
struct segtree {
    struct node {
        ll mx = 1e9, sec_mx = -INF;
        int cnt_mx = 0;
    };
    vector<node> tree;
    int n;
    segtree(int _n) : n(_n) {
        tree.resize(4 * n);
    }
    segtree() {}
    void pull(int v) {
        if (tree[v * 2 + 1].mx == tree[v * 2 + 2].mx) {
            tree[v].mx = tree[v * 2 + 1].mx;
            tree[v].cnt_mx = tree[v * 2 + 1].cnt_mx + tree[v * 2 + 2].cnt_mx;
            tree[v].sec_mx = max(tree[v * 2 + 1].sec_mx, tree[v * 2 + 2].sec_mx);
        } else if (tree[v * 2 + 1].mx > tree[v * 2 + 2].mx) {
            tree[v].mx = tree[v * 2 + 1].mx;
            tree[v].cnt_mx = tree[v * 2 + 1].cnt_mx;
            tree[v].sec_mx = max(tree[v * 2 + 1].sec_mx, tree[v * 2 + 2].mx);
        } else {
            tree[v].mx = tree[v * 2 + 2].mx;
            tree[v].cnt_mx = tree[v * 2 + 2].cnt_mx;
            tree[v].sec_mx = max(tree[v * 2 + 2].sec_mx, tree[v * 2 + 1].mx);
        }
    }
    void push(int v, int tl, int tr) {
        if (tr - tl == 1) return;
        if (tree[v * 2 + 1].mx > tree[v].mx) {
            tree[v * 2 + 1].mx = tree[v].mx;
        }
        if (tree[v * 2 + 2].mx > tree[v].mx) {
            tree[v * 2 + 2].mx = tree[v].mx;
        }
    }
    void set_min(int v, int tl, int tr, int l, int r, int x) {
        if (tree[v].mx <= x || tr <= l || r <= tl) return;
        if (tree[v].sec_mx < x && l <= tl && tr <= r) {
            tree[v].mx = x;
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        set_min(v * 2 + 1, tl, tm, l, r, x);
        set_min(v * 2 + 2, tm, tr, l, r, x);
        pull(v);
    }
    void set_min(int l, int r, int x) {
        set_min(0, 0, n, l, r, x);
    }
    ll get(int v, int tl, int tr, int pos) {
        if (pos < tl || pos >= tr) return -INF;
        if (tr - tl == 1) return tree[v].mx;
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return max(get(v * 2 + 1, tl, tm, pos), get(v * 2 + 2, tm, tr, pos));
    }
    ll get(int pos) {
        return get(0, 0, n, pos);
    }
};

struct monster {
    int h, r;
};
struct sword {
    int s, c;
};
map<int, int> lines;
vector<int> coords;
int n;
segtree odd, even;

void danya() {
    set<int> ls;
    int good = 0;
    auto query = [&](int k, int good) {
        k = k / 2;
        int to_add = good / 2;
        if (good % 2 == 1) {
            odd.set_min(0, k + 1, -to_add);
            even.set_min(0, k + 1, -to_add);
        } else {
            odd.set_min(0, k + 1, 1-to_add);
            even.set_min(0, k + 1, -to_add);
        }
    };
    for (int i = 0; i < n; ++i) {
        good++;
        ls.insert(coords[i]);
        good -= 2 * ls.count(lines[coords[i]]);
        query(i + 1, good);
    }
    good = 0;
    ls.clear();
    for (int i = 2 * n - 1; i >= n; --i) {
        good++;
        ls.insert(coords[i]);
        good -= 2 * ls.count(lines[coords[i]]);
        query(2 * n - 1 - i + 1, good);
    }
}
void solve() {
    int q;
    cin >> n >> q;
    odd = segtree(n / 2 + 1);
    even = segtree(n / 2 + 1);
    coords.resize(2 * n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        lines[x] = y;
        lines[y] = x;
        coords[i * 2] = x;
        coords[i * 2 + 1] = y;
    }
    vector<int> ks(q);
    for (auto &el : ks) {
        cin >> el;
    }
    sort(all(coords));
    danya();
    for (auto k : ks) {
        if (k % 2 == 1) {
            cout << max(0ll, k / 2 + odd.get(k / 2)) << ' ';
        } else {
            cout << max(0ll, k / 2 + even.get(k / 2)) << ' ';
        }
    }
}

#define LOCAL
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}