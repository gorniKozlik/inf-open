// #pragma GCC optimize("Ofast,inline,unroll-loops")
// #pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#include  <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;
using uint = unsigned int;

using oset = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)(x.size())

template<typename T>
void sort(T &s) {
    sort(all(s));
}

template<typename T>
void rsort(T &s) {
    sort(rall(s));
}

mt19937 rnd(264);

const int inf = 2e9 + 2000;
const ll infll = 2e18 + 2000;
const int st_R = 19;
const int R = (1 << st_R);
const int mod = 998244353;

struct Mod {
    int x = 0;
    Mod (int x) : x(x) {}
    Mod () = default;

    Mod operator + (const Mod o) const {
        if (x + o.x >= mod) {
            return x + o.x - mod;
        }
        return x + o.x;
    }

    Mod operator - (const Mod o) const {
        if (x - o.x < 0) {
            return x - o.x + mod;
        }
        return x - o.x;
    }

    Mod operator * (const Mod o) const {
        return ll(x) * ll(o.x) % ll(mod);
    }
};

Mod st(Mod x, int a) {
    Mod res = 1;
    while (a) {
        if (a & 1) {
            res = res * x;
        }
        x = x * x;
        a /= 2;
    }
    return res;
}

template<typename T>
struct point {
    T x, y;
    point(T x, T y) : x(x), y(y) {}
    point(point a, point b) : x(b.x - a.x), y(b.y - a.y) {}

    point operator + (const point o) const {
        return {x + o.x, y + o.y};
    }

    point operator - (const point o) const {
        return {x - o.x, y - o.y};
    }

    T operator * (const point o) const {
        return x * o.x + y * o.y;
    }

    T operator % (const point o) const {
        return x * o.y - y * o.x;
    }

    T len2() {
        return x * x + y * y;
    }

    ld len() {
        return sqrt(x * x + y * y);
    }
};

using Point = point<ll>;
using Vector = point<ll>;

struct Line {
    ld a, b, c;
    Line(ld a, ld b, ld c) : a(a), b(b), c(c) {}
    Line(Point p1, Point p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p2.x * p1.y) {}
};

struct Circle {
    Point c;
    ld r;
    Circle(Point c, ld r) : c(c), r(r) {}
};

int t[2 * R];
void build() {
    for (int i = R - 1; i; --i) {
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

int calc(int ql, int qr, int v = 1, int vl = 0, int vr = R) {
    if (vl >= qr || vr <= ql) {
        return 0;
    }

    if (vl >= ql && vr <= qr) {
        return t[v];
    }

    int vm = (vl + vr) / 2;

    return max(calc(ql, qr, v * 2, vl, vm), calc(ql, qr, v * 2 + 1, vm, vr));
}

struct Event {
    int x, ty;
    Event(int x, int ty) : x(x), ty(ty) {}

    bool operator < (const Event o) const {
        return x < o.x;
    }
};


void solve() {
    int n, q;
    cin >> n >> q;

    vector<Event> evs;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        evs.emplace_back(l, 1);
        evs.emplace_back(r, -1);
    }
    sort(evs);

    int cu = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (evs[i].ty == 1) {
            cu++;
        } else {
            cu--;
        }
        t[i + R] = cu;
    }
    build();

    for (int i = 0; i < q; ++i) {
        int cf;
        cin >> cf;
        cf--;

        int ma = calc(cf, 2 * n - cf);
        cout << max(0, (cf - ma + 2) / 2) << ' ';
    }
}

signed main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    int tt = 1;
    // cin >> tt;

    while (tt--) {
        solve();
    }
}
