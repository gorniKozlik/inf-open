#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

// #pragma GCC optimize("O3,unroll-loops,fast-math")
// #pragma GCC target("avx2,bmi2")

// #define int long long

using namespace std;
using namespace chrono;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

template<typename T, typename Cmp = less<T>>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, Cmp,
__gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template<typename T>
int sz(const T& x) {
    return (int)x.size();
}

const int MAXN = 1e6;
const ll INF = 4e18;
const int ALPH = 26;
const int MAXLOG = 20;
const ll MOD = 998244353;
const ld EPS = 1e-8;

const ull SEED = steady_clock::now().time_since_epoch().count();
mt19937_64 rnd(67);

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> stings(n);
    for (auto& [l, r] : stings) {
        cin >> l >> r;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << k / 2 << ' ';
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int test_cases = 1;
    // cin >> test_cases;
    while (test_cases--) solve();
    return 0;
}
