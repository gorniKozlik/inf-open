#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

using namespace std;
using ll = long long;
using ld = long double;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define int long long

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i].first >> d[i].second;
    }
    sort(d.begin(), d.end());
    vector<pair<int, int>> c;
    for (int i = 0; i < n; i++) {
        c.push_back({d[i].first, 0});
        c.push_back({d[i].second, 1});
    }
    sort(c.begin(), c.end());
    vector<int> answ(n + 1);
    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (c[i].second == 1) {
            cnt--;
        } else {
            cnt++;
        }
        if (i < n) {
            if (c[i].second == 1) {
                answ[i] = max(answ[i], cnt + 1);
                answ[i + 1] = max(answ[i + 1], cnt);
            } else {
                answ[i + 1] = max(answ[i + 1], cnt);
            }
        } else {
            int y = 2 * n - i - 1;
            if (c[i].second == 0) {
                answ[y] = max(answ[y], cnt);
                answ[y + 1] = max(answ[y + 1], cnt - 1);
            } else {
                answ[y + 1] = max(answ[y + 1], cnt + 1);
            }
        }
    }
    vector<int> ans(n + 1);
    for (int i = n; i > -1; i--) {
        if (i != n) {
            answ[i] = max(answ[i], answ[i + 1]);
        }
        ans[i] = (i + 1 - answ[i]) / 2;
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << max((int)0, ans[x]) << " ";
    }
}
