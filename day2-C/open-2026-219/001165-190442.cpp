// dimaloh

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using lll = __int128;
using pii = pair<int, int>;
using ld = long double;
using pll = pair<ll, ll>;

#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()


template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18;
const int inf = 1e9, mod = 1e9 + 7, sz = 5e5 + 10, logn = 20;
const ld pi = acosl(-1), eps = 1e-8;

mt19937 rnd(87438);

void solve() {
    int t; cin >> t;
    int n, m; cin >> n >> m;
    vector<int>v(n);
    for (auto &i : v) cin >> i;
    for (int i = 1; i < n; ++i) {
        if ((v[i - 1] + v[i]) % 2) {
            cout << "No";
            return;
        }
    }
    cout << "Yes\n";
    if (t == 1) return;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20);

    int t = 1;

#ifdef DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> t;
#endif


    while (t--) {
        solve();
        cout << '\n';
    }
}