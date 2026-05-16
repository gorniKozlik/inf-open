#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ll n,q;
    cin>>n>>q;
    vector <pair<ll,ll>> points;
    vector <pair<ll,ll>> lol(n);
    for (int i=0;i<n;i++) {
        cin>>lol[i].first>>lol[i].second;
        points.push_back({lol[i].first,1});
        points.push_back({lol[i].second,-1});
    }
    sort(points.begin(),points.end());

    ll c;
    cin>>c;
    ll op = 0;
    ll cnt =0;
    ll pl =0;
    ll pr = 2*n;
    ll res = 1e18;
    for (auto [l,r]:points) {
        op+=r;
        cnt++;
        pl++;
        pr--;
        if (pl>=c and pr>=c) {
            res = min(res,(c-op)/2+(c-op)%2);
        }

    }
    cout<<max((ll)0,res);

}