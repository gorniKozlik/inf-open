#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target ("avx2,bmi")
using namespace std;
// using namespace __gnu_pbds;
#define int long long
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
const int N = 1e6 + 10, mod = 998244353, inf = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++)cin >> l[i] >> r[i];
    vector<pair<int,int> > v;
    for (int i = 0; i < n; i++) {
        v.push_back({l[i], i + 1});
        v.push_back({r[i], -i - 1});
    }
    sort(v.begin(), v.end());
    int cnt = n;
    int q = 0, mx = 0, w = 0, mx1 = 0;
    vector<vector<int> > vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second > 0) {
            q++;
            cnt--;
        } else q--;
        if (mx < q) {
            mx1 = min(cnt, n - cnt - q);
            mx = q;
            w = i;
        }
        if (mx == q && mx1 < min(cnt, n - q - cnt)) {
            mx1 = max(mx1, min(cnt, n - cnt - q));
            mx = q;
            w = i;
        }
        if (q > 0)vec.push_back({q, min(cnt, n - cnt - q)});
    }
    vector<int> ans1(n + 1, inf);
    for (auto k: vec) {
        mx = k[0];
        w = k[1];
        vector<int> ans(n + 1);
        for (int i = 1; i <= mx; i++)ans[i] = 0;
        int i;
        for (i = mx + 1; i <= n; i += 2) {
            if (w == 0)break;
            w--;
            ans[i] = ans[i - 1] + 1;
            ans[i + 1] = ans[i];
        }
        for (; i <= n; i++)ans[i] = ans[i - 1] + 1;
        for (i = 1; i <= n; i++) {
            ans1[i] = min(ans[i], ans1[i]);
        }
    }
    while (m--) {
        int x;
        cin >> x;
        cout << ans1[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
