#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    vector<int> pnt;
    for (auto x : l) pnt.push_back(x);
    for (auto x : r) pnt.push_back(x);
    sort(pnt.begin(), pnt.end());
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    vector<int> ans(n + 1, INT_MAX);
    int mx = 0;
    vector<vector<int>> meow(n + 5);
    vector<vector<int>> meowp(n + 5);
    for (auto p : pnt) {
        int le = lower_bound(r.begin(), r.end(), p) - r.begin();
        int re = l.end() - upper_bound(l.begin(), l.end(), p);
        int now = n - le - re;
        
        mx = max(mx, now);
        meow[now + 1].push_back(now + 1);
    
        int start = now +  2 * min(le, re);
        meowp[start + 1].push_back(now + 1);
        int val = min(le, re);
        int v = min(le, re);
        le -= v; re -= v;
        int k_l = upper_bound(r.begin(), r.end(), p) - lower_bound(r.begin(), r.end(), p);
        int k_r = upper_bound(l.begin(), l.end(), p) - lower_bound(l.begin(), l.end(), p);
        int cnt = 0;
        while (true) {
            int z1 = min(k_l, re);
            re -= z1; k_l -= z1; k_r += z1; cnt += z1;
            int z2 = min(k_r, le);
            le -= z2; k_r -= z2; k_l += z2; cnt += z2;
            if (z1 == 0 && z2 == 0) break;
        }
        cout << endl;
        for (int j = 0; j < cnt; j++) {
            ans[start + j + 1] = min(ans[start + j + 1], val + j + 1);
        }
        //now + 2 + 2 * min(le, re)
    }
    for (int i = 1; i <= mx; i++) ans[i] = 0;
    multiset<int> qq;
    for (int i = 1; i <= n; i++) {
        for (auto x : meow[i]) qq.insert(x);
        for (auto x : meowp[i]) qq.erase(qq.lower_bound(x));
        if (!qq.empty()) {
            ans[i] = min(ans[i], (i - *qq.rbegin()) / 2 + 1);
        }
    }
    while (q--) {
        int x; cin >> x;
        cout << ans[x] << ' ';
    }
    return 0;
}