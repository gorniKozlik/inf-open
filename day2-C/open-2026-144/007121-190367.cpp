//#pragma optimize("O3")
//#pragma target("avx2, popcnt")
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define int long long

const int N = 2e5 + 5;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    vector<int> t(q); for (int& i : t) cin >> i;
    vector<int> L(n), R(n), RR(n), LL(n);
    iota(L.begin(), L.end(), 0);
    iota(R.begin(), R.end(), 0);
    sort(p.begin(), p.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });
    sort(L.begin(), L.end(), [&](int i, int j) {return p[i].first < p[j].first;});
    sort(R.begin(), R.end(), [&](int i, int j) {return p[i].second < p[j].second;});
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n));
    for (int i = 0; i < n; ++i) {
        LL[i] = p[L[i]].first;
        RR[i] = p[R[i]].second;
    }
    vector<int> L_(n), R_(n);
    for (int i = 0; i < n; ++i) {
        if (i == 0) L_[L[i]] = -1;
        else L_[L[i]] = L[i - 1];

        if (i == n - 1) R_[R[i]] = n;
        else R_[R[i]] = R[i + 1];
    }
    for (int i = 0; i < n; ++i) dp[i][i] = {0, 1};
    for (int i = n - 2; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (p[i].second > p[j].first) {
                dp[i][j] = {0, 2};
                continue;
            }
            // first open before j
            int r = L_[j];
            // first close after i
            int l = R_[i];
            int xr = p[r].first;
            int xl = p[l].second;
            if (xr <= xl) {
                // val in i ... j
                int RRR = upper_bound(RR.begin(), RR.end(), p[i].second) - RR.begin();
                int LLL = lower_bound(LL.begin(), LL.end(), p[j].first) - LL.begin();
                int val = LLL - RRR;
                dp[i][j] = {1, val + 2};
            } else {
                dp[i][j].first = dp[l][r].first + 1;
                dp[i][j].second = dp[l][r].second + 2;
            }
        }
    }
    vector<int> k(n + 1, n / 2);
    k[0] = 0, k[1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j)
            k[dp[i][j].second] = min(k[dp[i][j].second], dp[i][j].first);
    }
    for (int i : t) cout << k[i] << ' ';
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