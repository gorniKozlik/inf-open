#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cassert>
#include <ctime>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #pragma GCC optimize("Ofast")
// #pragma ivdep

using namespace std;
using ll = long long;
using ld = long double;
using lll = __int128;
using pii = pair<int, int>;
// using namespace __gnu_pbds;
// template<class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, q; cin >> n >> q;
    pair<int, int> e[n * 2];
    int ls[n];
    int rs[n];
    for (int i = 0; i < n; ++i) {
        cin >> ls[i] >> rs[i];
        e[i * 2] = {ls[i], 1};
        e[i * 2 + 1] = {rs[i], -1};
    }
    sort(ls, ls + n);
    sort(rs, rs + n);
    sort(e, e + n * 2);

    int cc = 0;
    vector<pair<int, int>> arr;
    for (int i = 0; i < n * 2; ++i) {
        int cl = lower_bound(rs, rs + n, e[i].first) - rs;
        int cr = n - (upper_bound(ls, ls + n, e[i].first) - ls);
        int fl = 0, fr = 0;
        if (e[i].second == 1) {
            cc++;
            e[i].second = 0;
            fr = 1;
        } else {
            fl = 1;
        }

        if (cl > cr) {
            arr.push_back({cc, cr * 2});
            if (fr)
                arr.push_back({cc - 1, cr * 2 + 2});

        } else if (cr == cr) {
            arr.push_back({cc, cl * 2});
            
        } else {
            arr.push_back({cc, cl * 2});
            if (fl)
                arr.push_back({cc - 1, cl * 2 + 2});
        }
        // cout << e[i].first << ' ' << cc << ' ' << cl << ' ' << cr << '\n';

        cc += e[i].second;
    }
    // cout << '\n';

    // sort(arr, arr + n * 2);
    // for (auto [c, m] : arr)
    //     cout << c << ' ' << m << '\n';

    int dp[n + 1] = {};
    for (auto [c, m] : arr)
        dp[c + m] = max(dp[c + m], c);
    for (int i = n - 1; i > 0; --i)
        dp[i] = max(dp[i], dp[i + 1]);

    // for (int i : dp)
    //     cout << i << ' ';
    // cout << '\n';

    for (int i = 0; i < q; ++i) {
        int k; cin >> k;
        // if (k <= arr[n * 2 - 1].first) {
        //     cout << "0 ";
        //     continue;
        // }
        cout << max(0, (k - dp[k] + 1) / 2) << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _ = 1;
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        cin >> _;
    #endif

    while (_--) {
        solve();
        cout << '\n';
    }

    return 0;
}
