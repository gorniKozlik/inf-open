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
    vector<int> ans(n + 1,1e18);
    int b = 0;
    int x = 0;
    for (auto v : t) {
        b-=v[1];
        if (v[1] == -1) {
            int k = b;
            int y = n - k - x;
            if (x == (n - 1) / 2) {
                for (int i = 0; i <= k; ++i) ans[i] = 0;
                int i = k + 1,cnt = 1;
            
                for (;cnt <= min(x,y) && i <= n; cnt++,i+=2) {
                    ans[i] = min(ans[i],cnt);
                    ans[i+1] = min(ans[i+1],cnt);
                }
                for (;i <=n; i++,cnt++) {
                    ans[i] = min(ans[i],cnt);
                }
            }
        }else {
            x++;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}