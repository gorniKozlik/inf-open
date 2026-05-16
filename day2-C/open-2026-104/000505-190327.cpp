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
        int j = min(i, 2 * n - i);
        ans[j] = min(ans[j], max(0ll, (cnt + j + 1) / 2 - cnt));
        if(j > 0){
            j--;
            ans[j] = min(ans[j], max(0ll, (cnt + j + 1) / 2 - cnt));
        }
        if(a[i].second == -1){
            cnt += a[i].second;
        }
    }
    for(int i = n - 2; i >= 0; i -= 2){
        ans[i] = min(ans[i], ans[i + 2] - 1);
    }
    for(int i = n - 3; i >= 0; i -= 2){
        ans[i] = min(ans[i], ans[i + 2] - 1);
    }
    while(q--){
        int k;
        cin >> k;
        cout << max(0ll, ans[k]) << " ";
    }
}
