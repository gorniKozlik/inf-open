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

    for (auto [l,r]:points) {
        op+=r;
        cnt++;
        if (cnt==n) {
            cout<<(n-op)/2;
            return 0;
        }

    }

}