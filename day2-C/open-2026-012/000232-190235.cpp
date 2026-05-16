#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
using ll = long long;
mt19937 rnd(52);
ll mod = 998244353;
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    cin.tie(nullptr);
    ios::sync_with_stdio(0);
#endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> ev(2*n+1);
    vector<pair<int,int>> otr;
    vector<int> in;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        otr.push_back({l, r});
        in.push_back(l);
        in.push_back(r);
    }
    sort(in.begin(), in.end());
    for (int i = 0; i < n; i++) {
        int l = otr[i].first;
        int r = otr[i].second;
        l = lower_bound(in.begin(), in.end(), l)-in.begin();
        r = lower_bound(in.begin(), in.end(), r)-in.begin();
        ev[l].push_back(1);
        ev[r+1].push_back(-1);
    }
    int cur = 0;
    int ended = 0;
    vector<int> ans(n, 1e9);
    for (int i = 0; i < 2*n; i++) {
        for (auto j:ev[i]) {
            if (j == -1) {
                ended++;
            }
            cur+=j;
        }
        int cnt = min(ended, n-ended-cur);
        //cout << cur << ' ' << cnt << endl;
        for (int j = 0; j < n; j++) {
            if (j < cur) {
                ans[j] = 0;
            }
            if (j > cur+2*cnt) {
                break;
            }
            ans[j] = min(ans[j], (j-cur)/2+1);
        }
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x-1] << ' ';
    }
    return 0;
}