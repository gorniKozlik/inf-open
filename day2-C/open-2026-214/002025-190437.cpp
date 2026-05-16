#include <iostream>
#include<vector>
#include<cmath>
#include<climits>
#include<map>
#include<set>
#include<algorithm>
#define int long long
#define F first
#define S second
using namespace std;
const int mod = 998244353;
const int N = 1e6;

signed main() {
    int n, q;
    cin>> n >> q;
    vector<pair<int,int>> arr(n);
    vector<pair<int,int>> e;
    for (int i =0;i< n; i++) {
        cin>> arr[i].F >> arr[i].S;
        e.push_back({arr[i].F, 0});
        e.push_back({arr[i].S, 1});
    }
    vector<int> ans(n+1,-1);
    sort(e.begin(), e.end());
    int cnt = 0, cnt1=0;
    vector<pair<int, int>> arr2;
    for (auto u: e) {
        arr2.push_back({cnt, min(cnt1, n-cnt-cnt1)});
        if (u.S==0){cnt++;}
        else{cnt--;cnt1++;}
    }
    sort(arr2.rbegin(), arr2.rend());
    int l = 0;
    for (auto u: arr2) {
        if (l>u.F+2*u.S){continue;}
        ans[max(l, u.F)] = u.F;l= u.F+2*u.S+1;
    }
    int h = arr2[0].F;
    for (int i =0;i<=arr2[0].F; i++){ans[i]=0;}
    for (int i =arr2[0].F+1;i<=n; i++) {
        if (ans[i]!=-1){h = ans[i];}
        ans[i] = (i-h+1)/2;
    }
    while (q--) {
        int t;
        cin>> t;
        cout << ans[t]<< endl;
    }
    return 0;
}