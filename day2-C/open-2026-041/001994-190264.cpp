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
        ll mn_cost = INF;
        int left = -1, right = -1;
    };
    vector<node> tree;
    int n;
    segtree(int _n) : n(_n), tree(1) {}
    ll get_mn_cost(int v) {
        return (v == -1 ? INF : tree[v].mn_cost);
    }
    void pull(int v) {
        tree[v].mn_cost = min(get_mn_cost(tree[v].left), get_mn_cost(tree[v].right));
    }
    void add(int v, int tl, int tr, int pos, ll val) {
        if (tr - tl == 1) {
            tree[v].mn_cost = min(tree[v].mn_cost, val);
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            if (tree[v].left == -1) {
                tree[v].left = sz(tree);
                tree.emplace_back();
            }
            add(tree[v].left, tl, tm, pos, val);
        } else {
            if (tree[v].right == -1) {
                tree[v].right = sz(tree);
                tree.emplace_back();
            }
            add(tree[v].right, tm, tr, pos, val);
        }
        pull(v);
    }
    void add(int pos, int val) {
        add(0, 0, n, pos, val);
    }
    ll get(int v, int tl, int tr, int l, int r) {
        if (v == -1 || tr <= l || r <= tl) return INF;
        if (l <= tl && tr <= r) return tree[v].mn_cost;
        int tm = (tl + tr) / 2;
        return min(get(tree[v].left, tl, tm, l, r), get(tree[v].right, tm, tr, l, r));
    }
    ll get(int l, int r) {
        return get(0, 0, n, l, r);
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
void danya(int k) {
    set<int> ls;
    int good = 0;
    for (int i = 0; i < k - 1; ++i) {
        good++;
        ls.insert(coords[i]);
        good -= 2 * ls.count(lines[coords[i]]);
    }
    int ans = 1e9;
    for (int i = k - 1; i < n; ++i) {
        good++;
        ls.insert(coords[i]);
        good -= 2 * ls.count(lines[coords[i]]);
        ans = min(ans, max(0, (k - good + 1) / 2));
    }
    cout << ans << ' ';
}
void solve() {
    int q;
    cin >> n >> q;
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
    for (auto k : ks) {
        danya(k);
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