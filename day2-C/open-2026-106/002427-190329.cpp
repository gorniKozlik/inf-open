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
    vector<int> mx(n + 1, -INF);
    for (int i = 0; i < 2 * n; i++) {
        now += scan[i].second;
        if (scan[i].second == -1) close++;
        int op = n - close - now;
        int mn = min(close, op);
        int can = mn * 2;
        ans[now] = 0;
        mx[now] = max(mx[now], now + can);
    }
    bool flag = false;
    for (int i = n; i >= 1; i--) {
        if (ans[i] == 0) flag = 1;
        if (flag) ans[i] = 0;
    }
    set<pair<int, int> > fir, sec;
    for (int i = 0; i <= n; i++) {
        while (!sec.empty()) {
            auto it = sec.begin();
            if ((*it).first < i) {
                auto p = *it;
                swap(p.first, p.second);
                fir.erase(p);
                sec.erase(sec.begin());
            } else break;
        }
        if (!fir.empty()) {
            auto p = *fir.begin();
            p.first = -p.first;
            int cost = (i - p.first + 1) / 2;
            ans[i] = min(ans[i], cost);
        }
        pair<int, int> p = {-i, mx[i]};
        fir.insert(p);
        swap(p.first, p.second);
        sec.insert(p);
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}
