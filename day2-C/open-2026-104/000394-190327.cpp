#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        a.push_back({l, 1});
        a.push_back({r, -1});
    }
    sort(a.begin(), a.end());
    vector<int> ans(n + 1, 1e9);
    int lop = 0, cnt = 0;
    for(int i = 0; i < 2 * n; i++){
        if(a[i].second == 1){
            cnt += a[i].second;
        }
        for(int j = 0; j <= min(i, 2 * n - i); j++){
            ans[j] = min(ans[j], max(0ll, (cnt + j + 1) / 2 - cnt));
        }
        if(a[i].second == -1){
            cnt += a[i].second;
        }
    }
    while(q--){
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}
