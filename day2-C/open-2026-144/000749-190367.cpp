//#pragma optimize("O3")
//#pragma target("avx2, popcnt")
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define int long long

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {int x, y; cin >> x >> y;}
    for (int i = 0; i < q; ++i) {int x; cin >> x; cout << x / 2 << ' ';}
}

int32_t main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    int test = 1; /*cin >> test*/
    while (test--)
        solve();
}