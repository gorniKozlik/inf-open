#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("avx2")
template<typename T>
istream& operator>>(istream& stream, vector<T>& a) {
    for (auto& x : a) stream >> x;
    return stream;
}
template<typename T>
ostream& operator<<(ostream& stream, vector<T>& a) {
    for (auto& x : a) stream << x << ' ';
    cout << '\n';
    return stream;
}
template<typename T1, typename T2>
istream& operator>>(istream& stream, vector<pair<T1, T2>>& a) {
    for (auto& [x, y] : a) stream >> x >>  y;
    return stream;
}
template<typename T1, typename T2>
ostream& operator<<(ostream& stream, vector<pair<T1, T2>>& a) {
    for (auto& [x, y] : a) stream << x << ' ' << y << '\n';
    return stream;
}
template<typename T1, typename T2>
inline void amax(T1& a, T2 b) {
    a = max(a, b);
}
template<typename T1, typename T2>
inline void amin(T1& a, T2 b) {
    a = min(a, b);
}

#define int int64_t
#define all(x) x.begin(), x.end()
#define pb emplace_back
#define ff first
#define ss second
#define sz(x) (int)(x.size())
#define deb cout << "----------------------" << endl
#define MIN(x) *min_element(all(x))
#define MINID(x) min_element(all(x)) - x.begin()
#define MAX(x) *max_element(all(x))
#define MAXID(x) max_element(all(x)) - x.begin()
#define push emplace
#define SUM(x) accumulate(all(x), 0ll)
#define sj(x) sort(all(x)), x.erase(unique(all(x)), x.end())

mt19937 rnd(221);

using ll = long long;
using vi = vector<int>;
using pi = pair<int,int>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using ld = long double;

const int64_t INF = 1e18;
const int INF2 = 1e9;
const int mod = 1e9+7;
const ld eps = 1e-6;

const int N = 1e5 + 2323;
const int D = 500;


void solve() {
    int n, q; cin >> n >> q;
    vpi a(n); cin >> a;
    vi ans(n + 1, INF);
    vpi ev;
    for (auto [l, r] : a) {
        ev.pb(l, -1);
        ev.pb(r, 1);
    }
    sort(all(ev));
    int bulo = 0;
    int bal = 0;
    for (auto [x, t] : ev) {
        if (t == -1) bal -= t;
        int pr = bulo;
        int levo = n - (pr + bal);
        int cu = bal;
        for (int dop = 0; dop <= min(pr, levo); dop++) {
           // if (min(n, cu) > 10) break;
            amin(ans[min(n, cu)], dop);
            if (min(pr, levo) != dop) cu += 2;
        }
        for (int dop2 = 1; dop2 <= bal; dop2++) {
           // if (min(n, cu) > 10) break;
            cu++;
            amin(ans[min(n, cu)], min(pr, levo) + dop2);
        }

        if (t == 1) bal-=t;

        if (t == 1) bulo++;
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }

    while (q--) {
        int x; cin >> x;
        cout << ans[x] << ' ';
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(20);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
    }
}