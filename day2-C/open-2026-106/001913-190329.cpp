#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
#define int long long
const int MOD = 998244353;
const int INF = 1e18;

using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

void solve1();

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int qwerty = 1;
    // cin >> qwerty;
    while (qwerty--) {
        solve1();
    }
}

void solve1() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<pair<int, int> > scan;
    for (int i = 0; i < n; i++) {
        scan.push_back({a[i].first, 1});
        scan.push_back({a[i].second + 1, -1});
    }
    sort(scan.begin(), scan.end());
    int close = 0, now = 0;
    vector<int> ans(n + 1, INF);
    for (int i = 0; i < 2 * n; i++) {
        now += scan[i].second;
        if (scan[i].second == -1) close++;
        int op = n - close - now;
        int mn = min(close, op);
        int can = mn * 2;
        for (int j = 1; j <= now; j++) {
            ans[j] = 0;
        }
        for (int j = now + 1; j <= now + can; j++) {
            ans[j] = min(ans[j], (j - now + 1) / 2);
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}
