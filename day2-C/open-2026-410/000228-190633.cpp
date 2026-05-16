#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    ll i,j,n,k,t,q;
    cin>>n>>q;
    for (i=0;i<n;i++) {
        cin>k>>t;
    }
    while (q--) {
        cin>>k;
        if (k==1) {
            cout<<0<<" ";
        }
        else {
            if (n&1) {
                cout<<k/2<<" ";
            }
            else {
                cout<<(k+1)/2<<" ";
            }
        }
    }
    cout<<'\n';
    return 0;
}