#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int INF = 1e9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    vector<pair<int, int> > sc(0);
    for (int i = 0; i < n; i++) {
        a[i].first *= 2;
        a[i].second *= 2;
        sc.push_back({a[i].first, -1});
        sc.push_back({a[i].second, 1});
        sc.push_back({a[i].first + 1, 0});
        sc.push_back({a[i].first - 1, 0});
    }
    int otk = 0, z = 0;
    sort(sc.begin(), sc.end());
    for (int i = 0; i < sc.size(); i++) {
        int type = sc[i].second;
        if (type == -1) {
            otk++;
        }
        if (type == 1) {
            otk--;
            z++;
        }
        if (type == 0) {
            int otr = otk;
            for (int j = 0; j <= otr; j++) {
                dp[j] = 0;
            }
            int h = 2 * n - 2 * otr - 2 * z;
            int l = h / 2;
            for (int y = 1; y <= 2 * min(l, z); y++) {
                dp[otr + y] = min(dp[otr + y], (y + 1) / 2);
            }
        }
    }
    //cout << 2 * otk + 2 * z << endl;
    for (int i = 1; i <= q; i++) {
        int x;
        cin >> x;
        cout << dp[x] << " ";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}