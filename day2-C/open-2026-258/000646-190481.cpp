#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<int> l(n),r(n);
    set<int> s;
    for(int i = 0;i < n;i++){
        cin >> l[i] >> r[i];
        s.insert(l[i]);
        s.insert(r[i]);
    }
    int j = 0;
    map<int,int> mm;
    for(int u : s){
        mm[u] = j;
        j++;
    }
    for(int i = 0;i < n;i++){
        l[i] = mm[l[i]];
        r[i] = mm[r[i]];
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    vector<pair<int,int>> vv;
    vector<int> ans(n + 1);
    for(int i = 0;i < 2*n - 1;i++){
        auto u = upper_bound(r.begin(),r.end(),i);
        int y1 = u - r.begin();
        auto u1 = lower_bound(l.begin(),l.end(),i + 1);
        int y2 = l.end() - u1;
        int x = n - y1 - y2,y = min(y1,y2);
        vv.push_back({x,y});
    }
    sort(vv.begin(),vv.end());
    reverse(vv.begin(),vv.end());
    int ma = vv[0].first,ma1 = vv[0].first;
    for(auto u : vv){
        int x = u.first,y = u.second;
        if(x + 2*y > ma){
            for(int i = ma + 1;i <= x + 2*y;i++){
                ans[i] = (i - x + 1) / 2;
            }
            ma = x + 2*y;
        }
    }
    while(q--){
        int k;
        cin >> k;
        if(k <= ma1){
            cout << 0 << " ";
            continue;
        }
        cout << ans[k] << " ";
    }
    return 0;
}
