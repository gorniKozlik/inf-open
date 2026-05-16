// # define _GLIBCXX_DEBUG
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC optimize("trapv")
#include <bits/extc++.h>

using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

# define int long long
# define all(v) v.begin(),v.end()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#elif DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    for (auto &elem: seg)
        cin >> elem.first >> elem.second;
    while (q--) {
        int x;
        cin >> x;
        cout << x / 2 << "\n";
    }
    return 0;
}
