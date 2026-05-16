#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("03")
#pragma GCC optimize("unroll-loops")

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()


using pii = pair <int, int>;
const int inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k; cin >> n >> k;
    vector <int> keys = {0, inf + 1};
    vector <int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        keys.emplace_back(l[i]);
        keys.emplace_back(r[i]);
        keys.emplace_back(l[i] + 1);
    }
    sort(all(keys));
    keys.erase(unique(all(keys)), keys.end());
    int m = (int)keys.size();
    vector <vector <int>> add(m), del(m);
    for (int i = 0; i < n; ++i) {
        l[i] = lower_bound(all(keys), l[i]) - keys.begin();
        r[i] = lower_bound(all(keys), r[i]) - keys.begin();
        add[l[i]].emplace_back(i);
        del[r[i]].emplace_back(i);
    }
    vector <int> freq(m, -inf), can(m, -inf);
    int left = 0, right = n;
    for (int i = 0; i < m; ++i) {
        right -= (int)add[i].size();
        left += (int)del[i].size();
        freq[i] = n - left - right;
        can[i] = min(left, right);
    }
    while (k--) {
        int x; cin >> x;
        int ans = inf;
        for (int i = 0; i < m; ++i) {
            if (freq[i] >= x) ans = 0;
            else if (x - freq[i] <= can[i] * 2) ans = min(ans, (x - freq[i] + 1) / 2);
        }
        cout << ans << ' ';
    }
}