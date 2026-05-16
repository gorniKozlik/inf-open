#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18, MOD = 1e9 + 7;
mt19937 rnd(time(0));

void solve();

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> z;
    vector<int> x;
    vector<int> y;
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        z.push_back({l, 1});
        z.push_back({r + 1, -1});
        x.push_back(l);
        y.push_back(r);
    }
    sort(z.begin(), z.end());
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    vector<vector<pair<int, int>>> res(n + 1);
    int mx = 0, bal = 0;
    for (int i = 0; i < (int)z.size(); i++){
        bal += z[i].second;
        mx = max(mx, bal);
        if (i != (int)z.size() - 1){
            res[bal].push_back({z[i].first, z[i + 1].first - 1});
        }
    }
    vector<vector<int>> add(n + 1);
    for (int i = 0; i <= n; i++){
        int mm = 0;
        for (auto [a, b] : res[i]){
            int c1 = lower_bound(y.begin(), y.end(), a) - y.begin(), c2 = n - (upper_bound(x.begin(), x.end(), b) - x.begin());
            mm = max(mm, min(c1, c2));
        }
        for (int j = 0; j < mm; j++){
            add[i].push_back(2);
        }
        for (int j = 0; j < n - i - 2 * mm; j++){
            add[i].push_back(1);
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++){
        ans = min(ans, (int)add[i].size());
    }
    while (q--){
        int k;
        cin >> k;
        cout << ans << " ";
    }
}

