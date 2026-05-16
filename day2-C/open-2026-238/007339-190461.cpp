#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<array<int,2>> a(n),t;
    for (int i= 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        t.push_back({a[i][0],-1});
        t.push_back({a[i][1],1});
    }
    sort(t.begin(),t.end());
    vector<int> h,g(q,1e18);
    for (int i = 0; i < q; ++i){
        int k;
        cin >> k;
        h.push_back(k);
    }
    vector<int> ans(n + 1,1e18);
    int b = 0;
    int x = 0;
    vector<int> x1(n + 1,-1);
    int mx = 0;
    for (auto v : t) {
        b-=v[1];
        if (v[1] == -1) {
            int k = b;
            mx = max(mx,k);
            int y = n - k - x;
            x1[k] = max(x1[k],min(x,y));
        }else {
            x++;
        }
    }
    ans[0] = 0;
    ans[1] = 0;
    set<int> y;
    vector<vector<int>> d(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j : d[i]) {
            y.erase(j);
        }
        if (i<= mx) ans[i] = 0;
        ans[i] = min(ans[i],ans[i-1] + 1);
        if (x1[i]>=1) {
            y.insert(i);
            if (i + 2 * x1[i]<n) {
                d[i + 2 * x1[i] + 1].push_back(i);
            }
        }
        if (!y.empty()) {
            int k = *(y.rbegin());
            ans[i] = min(ans[i],(i - k + 1) / 2);
        }
    }
    for (int i : h) cout << ans[i] << ' ';
}