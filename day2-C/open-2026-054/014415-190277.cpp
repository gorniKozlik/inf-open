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
    vector<ll> w, ends;
    for (ll i = 0; i<n; i++){
        ll l, r;
        cin>>l>>r;
        w.push_back(l);
        w.push_back(r+1);
        w.push_back(r);
        ends.push_back(r);
        v.push_back({l, 1});
        v.push_back({r+1, -1});
    }
    sort(w.begin(), w.end());
    for (auto&e:v){
        e.x = lower_bound(w.begin(), w.end(), e.x) - w.begin();
    }
    for (auto&e:ends){
        e = lower_bound(w.begin(), w.end(), e) - w.begin();
    }
    sort(v.begin(), v.end(), comp);
    sort(ends.begin(), ends.end());
    n *=2;
    ll ind = 0;
    ll m = v.size();
    ll bal = 0;
    ll a = 0;
    vector<ll> ans(n+1, 0);
    vector<vector<ll>> of(n+2), ans1(n+1), off(n+2);
    ll ind1 = 0;
    for (ll i = 0; i<m; i++){
        if (i){
            if (w[i-1] == w[i]){continue;}
        }
        ll b1 = 0;
        ll b = 0;
        while (ind1 != n/2){
            if (ends[ind1] > i){break;}
            b1++;
            ind1++;
        }
        while (ind != n){
            if (v[ind].x > i){break;}
            bal += v[ind].t;
            if (v[ind].t == -1){
                a++;
            }
            else{
                b++;
            }
            ind++;
        }
        ans[bal]++;
        ll c = n/2 - a - b - b1 - (bal - b1 - b);
        ll pl = min(a, c)*2;
        ll las = bal + pl;
        // if (bal == 2){
        //     cout<<a<<'+'<<b<<' '<<b1<<'!'<<c<<endl;
        //     cout<<las<<'@'<<w[i]<<endl;
        // }
        of[las+1].push_back(bal);

        ll ost = max(a, c) - min(a, c);
        if (a > c){
            pl += min(ost, b);
        }
        else{
            pl += min(ost, b1);
        }
        // if (w[i] == 15){
        //     cout<<'@'<<i<<endl;
        //     cout<<a<<'+'<<b<<' '<<b1<<'!'<<c<<endl;
        //     cout<<bal<<'!'<<las<<' '<<bal+pl<<endl;
        // }
        ans1[las+1].push_back(pl/2);
        off[bal+pl+1].push_back(pl/2-(las+1));
    }
    vector<ll> otv(n+1, 1e18);
    multiset<ll> qq;
    multiset<ll> q1;
    for (ll i = 0; i<n+1; i++){
        for (ll j = 0; j<ans[i]; j++){
            qq.insert(-i);
        }
        for (auto&e:ans1[i]){
            q1.insert(-i+e);
        }
        for (auto&e:off[i]){
            q1.erase(q1.lower_bound(e));
        }
        for (auto&e:of[i]){
            qq.erase(qq.lower_bound(-e));
        }
        // if (i == 6){for (auto&e:qq){cout<<e<<'!';}}cout<<endl;
        if (qq.size()){
            otv[i] = (i + (*qq.begin()))/2;
            otv[i] += (i + (*qq.begin()))%2;
        }
        if (q1.size()){
            otv[i] = min(otv[i], i + 1 + (*q1.begin()));
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