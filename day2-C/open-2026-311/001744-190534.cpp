#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize("Ofast")
using ll = long long;
using ld = long double;
using vl = __int128_t;
using ull = unsigned long long;
#define pb emplace_back
#define all(x) (x).begin(), (x).end()
constexpr int mod = 998244353;
const int LG = 19;
const int N = 200000;
int stmin[LG][N];
int stmax[LG][N];
// [l, r)
int getmax(int l, int r) {
    int lg = __lg(r - l);
    return max(stmax[lg][l], stmax[lg][r - (1 << lg)]);
}
int getmin(int l, int r) {
    int lg = __lg(r - l);
    return min(stmin[lg][l], stmin[lg][r - (1 << lg)]);
}
void solve() {
    int n, q;
    cin >> n>> q;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    int k;
    cin >> k;
    sort(all(a), [](const pair<int,int> &x, const pair<int,int> &y) -> bool {
        if (x.first == y.first) {
            return x.second < y.second;
        }
        return x.first < y.first;
    });
    for (int i = 0; i < n; ++i) {
        stmax[0][i] = a[i].first;
        stmin[0][i] = a[i].second;
    }
    for (int i = 1; i < LG; ++i) {
        for (int j = 0; j < n; ++j) {
            stmax[i][j] = max(stmax[i - 1][j], stmax[i - 1][min(n - 1, j + (1 << (i - 1)))]);
            stmin[i][j] = min(stmin[i - 1][j], stmin[i - 1][min(n - 1, j + (1 << (i - 1)))]);
        }
    }
    int ans = n;
    for (int i = 0; i < n; ++i) {
        int left = i, right = n;
        while (left < right - 1) {
            int mid = (left + right) / 2;
            int mxl = getmax(i, mid + 1);
            int mnr = getmin(i, mid + 1);
            if (mnr >= mxl) {
                left = mid;
            } else {
                right = mid;
            }
        }
        ans = min(ans, max(i, n - left - 1));
    }
    cout << ans;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
