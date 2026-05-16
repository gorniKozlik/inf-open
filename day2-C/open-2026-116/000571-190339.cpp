#include <bits/stdc++.h>

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
#define int long long

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    vector<int> ans(n + 1, (int) 1e18), x;
    for (int i = 0; i < n; i++) x.emplace_back(a[i].first), x.emplace_back(a[i].second);
    sort(x.begin(), x.end());
    ordered_set left, right;
    for (int i = 0; i < n; i++) left.insert(a[i].first), right.insert(a[i].second);
    vector<pair<int, int> > t[2][n + 1];
    for (int i: x) {
        int c1 = (int) right.order_of_key(i),
                c2 = (int) left.size() - (int) left.order_of_key(i + 1), inter = n - c1 - c2;
        ans[inter] = 0;
        t[inter % 2][inter].emplace_back(0, inter);
        if (inter + min(c1, c2) * 2 + 2 <= n)
            t[inter % 2][inter + min(c1, c2) * 2 + 2].emplace_back(1, inter);
        c1 = (int) right.order_of_key(i),
                c2 = (int) left.size() - (int) left.order_of_key(i), inter = n - c1 - c2;
        ans[inter] = 0;
        t[inter % 2][inter].emplace_back(0, inter);
        if (inter + min(c1, c2) * 2 + 2 <= n)
            t[inter % 2][inter + min(c1, c2) * 2 + 2].emplace_back(1, inter);
        c1 = (int) right.order_of_key(i + 1),
                c2 = (int) left.size() - (int) left.order_of_key(i), inter = n - c1 - c2;
        ans[inter] = 0;
        t[inter % 2][inter].emplace_back(0, inter);
        if (inter + min(c1, c2) * 2 + 2 <= n)
            t[inter % 2][inter + min(c1, c2) * 2 + 2].emplace_back(1, inter);
    }
    for (int r = 0; r < 2; r++) {
        multiset<int> start;
        for (int j = r; j <= n; j += 2) {
            for (auto [begin, end]: t[r][j]) {
                if (begin == 0)
                    start.insert(j);
                else
                    start.erase(start.find(end));
            }
            if (!start.empty())
                ans[j] = min(ans[j], (j - *start.rbegin()) / 2);
        }
    }
    for (int i = n - 1; i >= 0; i--)
        ans[i] = min(ans[i], ans[i + 1]);
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    return 0;
}
