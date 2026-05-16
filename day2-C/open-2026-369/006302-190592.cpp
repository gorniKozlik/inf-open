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

    vector <ll> quer(q);
    for (int i=0;i<q;i++) {
        cin>>quer[i];
    }
    ll op = 0;
    ll cnt =0;
    ll pl =0;
    ll pr = 2*n;
    ll res = 1e18;
    vector <ll> kek(n+2,0);
    for (auto [l,r]:points) {
        op+=r;
        cnt++;
        pl++;
        pr--;
        kek[min(pr,pl)]=max(kek[min(pl,pr)],op);
    }
    for (int i=n;i>=0;i--) {
        kek[i]=max(kek[i+1],kek[i]);
    }

    for (int i=0;i<q;i++) {
        cout<<max((ll)0,(quer[i]-kek[quer[i]])/2+(quer[i]-kek[quer[i]])%2);
    }

}