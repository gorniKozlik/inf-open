#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    ll i,j,n,k,t,q;
    cin>>n>>q;
    vector<pair<ll,ll>>ev(4*n-1);
    ll it=0;
    for (i=0;i<n;i++) {
        ll l,r;
        cin>>l>>r;
        l*=2;
        r*=2;
        ev[it]={l,1};
        it++;
        ev[it]={r,-1};
        it++;
    }
    sort(ev.begin(),ev.begin()+2*n);
    for (i=1;i<2*n;i++) {
        ev[it]={(ev[i-1].first+ev[i].first)/2,0};
        it++;
    }
    sort(ev.begin(),ev.end());
    vector<ll>L(2*n-1),R(2*n-1);
    ll left=n,right=0;
    it=0;
    for (i=0;i<4*n-1;i++) {
        if (ev[i].second==1) {
            left--;
        }
        else if (ev[i].second==-1) {
            right++;
        }
        else {
            L[it]=left;
            R[it]=right;
            it++;
        }
    }
    while (q--) {
        cin>>k;
        ll mn=1e18;
        for (i=0;i<2*n-1;i++) {
            ll todo=k-(n-R[i]-L[i]);
            if (todo<=0) {
                mn=0;
            }
            else {
                if (todo<=2*min(L[i],R[i])) {
                    mn=min(mn,(todo+1)/2);
                }
            }
        }
        cout<<mn<<" ";
    }
    return 0;
}