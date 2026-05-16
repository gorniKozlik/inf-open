// #define _GLIBCXX_DEBUG
// #pragma GCC optimize("O3,unroll-loops")
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
using ll = long long;
using ld = long double;
struct ev{
    ll x, t;
};
bool comp(ev&a, ev&b){
    return a.x < b.x;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, q;
    cin>>n>>q;
    vector<ev> v;
    vector<ll> w;
    for (ll i = 0; i<n; i++){
        ll l, r;
        cin>>l>>r;
        w.push_back(l);
        w.push_back(r+1);
        v.push_back({l, 1});
        v.push_back({r+1, -1});
    }
    sort(w.begin(), w.end());
    for (auto&e:v){
        e.x = lower_bound(w.begin(), w.end(), e.x) - w.begin();
    }
    sort(v.begin(), v.end(), comp);
    n *=2;
    ll ind = 0;
    ll m = v.size();
    ll bal = 0;
    ll cnt = 0;
    vector<ll> ans(n+1, 0);
    vector<vector<ll>> of(n+2);
    ll ma = 0;
    for (ll i = 0; i<m; i++){
        while (ind != n){
            if (v[ind].x > i){break;}
            bal += v[ind].t;
            if (v[ind].t == -1){
                cnt+=2;
            }
            ind++;
        }
        ma = max(ma, bal);
        ans[bal]++;
        ll pl = min(cnt, n - cnt - bal);
        ll las = bal + pl;
        if (pl%2 == 1){
            las++;
        }
        of[las].push_back(bal);
    }
    // for (auto&e:ans){cout<<e<<'_';}cout<<endl;
    vector<ll> otv(n+1, 1e18);
    multiset<ll> qq;
    for (ll i = 0; i<n+1; i++){
        for (ll j = 0; j<ans[i]; j++){
            qq.insert(-i);
            // cout<<'+'<<i<<endl;
        }
        for (auto&e:of[i]){
            qq.erase(qq.lower_bound(-e));
            // cout<<"-"<<e<<endl;
        }
        if (qq.size()){
            // if (i == 6){
            //     cout<<'@'<<(i + (*qq.begin()))<<endl;
            // }
            otv[i] = (i + (*qq.begin()))/2;
            otv[i] += (i + (*qq.begin()))%2;
        }
    }
    // for (auto&e:otv){cout<<e<<'_';}cout<<endl;
    while(q--){
        ll k;
        cin>>k;
        cout<<otv[k]<<' ';
    }
    cout<<endl;
    return 0;
}