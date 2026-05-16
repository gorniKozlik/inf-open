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
    sort(all(a));
    /*
    for (int i = 0; i < n; ++i) {
        stmax[0][i] = a[i].first;
        stmin[0][i] = a[i].second;
    }
    for (int i = 1; i < LG; ++i) {
        for (int j = 0; j < n; ++j) {
            stmax[i][j] = max(stmax[i - 1][j], stmax[i - 1][min(n - 1, j + (1 << (i - 1)))]);
            stmin[i][j] = min(stmin[i - 1][j], stmin[i - 1][min(n - 1, j + (1 << (i - 1)))]);
        }
    }*/
    set<pair<int,int>> rs, ls;
    vector<int> ans(n + 1, n);
    for (int i = 0; i < n; ++i) {
        int j = i;
        int skip = 0;
        while (j < n) {
            if (a[j].first > a[i].second) break;
            rs.insert({a[j].second, a[j].first});
            ls.insert({a[j].first, a[j].second});
            while (rs.begin()->first < ls.rbegin()->first) {
                skip++;
                auto [r, l] = *rs.begin();
                rs.erase(rs.begin());
                ls.erase({l, r});
            }
            int sz = (int) ls.size();
            ans[sz] = 0;
            int lft = skip + i, rgt = n - j - 1;
            int x = sz + 2;
            int cur = 1;
            while (x <= n && min(lft, rgt) > 0) {
                ans[x] = min(ans[x], cur++);
                rgt--;
                lft--;
                x += 2;
            }
            x--;
            for (;x <= n && max(rgt, lft) > 0;) {
                ans[x] = min(ans[x], cur++);
                rgt--;
                lft--;
                x++;
            }
            j++;
        }
        rs.clear();
        ls.clear();
    }
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
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
