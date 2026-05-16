//#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define cin(v) for (auto& el : v) {cin >> el;}
#define cout(v) for(auto& el : v) {cout << el << " ";} cout << "\n";

using namespace std;
using ll = long long;
using db = double;
const ll MOD = 1e9 + 7;
const ll MOD2 = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ps;
    for (int i = 0; i < n; i++) {
        int l,r;
        cin >> l >> r;
        ps.push_back({l, 0});
        ps.push_back({r, 1});
    }
    sort(all(ps));
    int cnt_l = 0, cnt_r = 0;
    int cnt_cur = 0;
    vector<int> ans(n + 1, n);
    vector<vector<int>> add(n + 1);
    for (int i = 0; i< ps.size(); i++) {
        int cnt_add = min(n - cnt_l, cnt_r);
        /*for (int j = 0; j <= cnt_add; j++) {
            ans[cnt_cur + 2 * j] = min(ans[cnt_cur + 2 * j], j);
        }*/
        add[cnt_cur + 2 * cnt_add].push_back(cnt_add);
        if (ps[i].second == 0) {
            cnt_cur++;
            cnt_l++;
        }
        if (ps[i].second == 1) {
            cnt_cur--;
            cnt_r++;
        }
    }
    int min_ = n + 73;
    for (int i = n; i >= 0; i -= 2) {
        min_--;
        for (int j : add[i]) {
            min_ = min(min_, j);
        }
        ans[i] = min_;
    }
    min_ = n + 73;
    for (int i = n - 1; i >= 0; i -= 2) {
        min_--;
        for (int j : add[i]) {
            min_ = min(min_, j);
        }
        ans[i] = min_;
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    return;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int multitest = 0;
    if (multitest) {
        int t;
        cin >> t;
        while (t--) {
            solve();
        }
    } else {
        solve();
    }
}