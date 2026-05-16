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
    }
    q = 0;
    vector<int> ans(n + 1);
    for (int i = 1; i <= mx; i++)ans[i] = 0;
    set<int> s;
    for (int i = 0; i <= w; i++) {
        if (v[i].second > 0) {
            q++;
            s.insert(v[i].second - 1);
        } else {
            q--;
            s.erase(-v[i].second - 1);
        }
    }
    int l1 = inf, r1 = -inf;
    for (auto k: s) {
        l1 = min(l1, l[k]);
        r1 = max(r1, r[k]);
    }
    int cntl = 0, cntr = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] < l1)cntl++;
        if (l[i] > r1)cntr++;
    }
    int i;
    for (i = mx + 1; i <= n; i += 2) {
        if (cntl == 0 || cntr == 0)break;
        cntl--;
        cntr--;
        ans[i] = ans[i - 1] + 1;
        ans[i + 1] = ans[i];
    }
    for (; i <= n; i++)ans[i] = ans[i - 1] + 1;
    while (m--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
