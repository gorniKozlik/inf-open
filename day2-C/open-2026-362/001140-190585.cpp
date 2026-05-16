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
const int INF = 2e9;
const int ALPH = 26;
const int MAXLOG = 20;
const ll MOD = 998244353;
const ld EPS = 1e-8;

const ull SEED = steady_clock::now().time_since_epoch().count();
mt19937_64 rnd(67);

struct Event {
    int x, type;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<Event> stings;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        stings.emplace_back(Event {l, 1});
        stings.emplace_back(Event {r, -1});
    }
    sort(stings.begin(), stings.end(),
    [](Event a, Event b) -> bool {
        if (a.x == b.x) {
            return a.type > b.type;
        }
        return a.x < b.x;
    });
    int balance = 0;
    pair<int, int> max_covered = {0, -INF};
    for (int i = 0; i < 2 * n; i++) {
        auto [x, type] = stings[i];
        balance += type;
        max_covered = max(max_covered, make_pair(balance,
        min(((i + 1) - balance) / 2, (2 * n - (i + 1) - balance) / 2)));
    }
    while (q--) {
        int k;
        cin >> k;
        if (k <= max_covered.first) {
            cout << "0\n";
        } else if (k <= max_covered.first + 2 * max_covered.second) {
            cout << (k - max_covered.first + 1) / 2 << '\n';
        } else {
            cout << max_covered.second + (k - max_covered.first - 2 * max_covered.second) << '\n';
        }
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
