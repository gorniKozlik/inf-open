#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
using dbl=double;
dbl const PI=acos(-1.0);
ll const mod=998244353;
ll const inf=1e18;
void gg(){
    cout<<1<<endl;
}
ll bit(ll x,ll i){
    return((x>>i)&1);
}


void solve(){
    ll n,q;
    cin>>n>>q;
    vector<pair<pll,ll>> a(n),b=a;
    vector<ll> v={-1};
    for(ll i=0;i<n;i++){
        ll l,r;
        cin>>l>>r;
        a[i]={{l,r},i};
        b[i]={{r,l},i};
        v.push_back(l);
        v.push_back(r);
        v.push_back(l-1);
        v.push_back(r+1);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end())-v.begin());
    for(auto[I,i]:a){
        auto[l,r]=I;
        l=lower_bound(v.begin(),v.end(),l)-v.begin();
        r=lower_bound(v.begin(),v.end(),r)-v.begin();
        a[i]={{l,r},i};
    }
    for(auto[I,i]:b){
        auto[r,l]=I;
        l=lower_bound(v.begin(),v.end(),l)-v.begin();
        r=lower_bound(v.begin(),v.end(),r)-v.begin();
        b[i]={{r,l},i};
    }
    ll m=v.size();
    vector<ll> pref(m+2),p(m+2),s(m+2);
    for(auto[I,i]:a){
        auto[l,r]=I;
        pref[l]++;
        pref[r]--;
        p[r]++;
        s[l]++;
    }
    ll kmi=pref[0];
    for(ll i=1;i<=m;i++){
        pref[i]+=pref[i-1];
        kmi=max(kmi,pref[i]);
        p[i]+=p[i-1];
        s[m-i+1]+=s[m-i+2];
    }
    vector<ll> otv(2*n+2,n);
    for(ll i=1;i<=m;i++){
        ll d=abs(p[i-1]-s[i+1]);
        ll mx=max(p[i-1],s[i+1]);
        ll mi=mx-d;
        ll val=mi;
        ll idx=pref[i]+2*val;
        for(ll j=idx,sum=0;j>=kmi;j-=2,sum++){
            otv[j]=min(otv[j],val-sum);
            if(d!=0){
                otv[j+1]=min(otv[j+1],val-sum+1);
                otv[j-1]=min(otv[j-1],val-sum);
            }
        }
        if(d!=0){
            otv[idx+1]=min(otv[idx+1],val+1);
        }
    }

    while(q--){
        ll x;
        cin>>x;
        if(x<=kmi){
            cout<<0<<'\n';
            continue;
        }
        cout<<otv[x]<<'\n';
    }

}
int main()
{
    ll tqqq=1;
    //cin>>tqqq;
    while(tqqq--){
        solve();
        cout<<'\n';
    }

    return 0;
}
