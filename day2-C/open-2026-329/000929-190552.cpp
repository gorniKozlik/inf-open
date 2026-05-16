#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define fi first
#define se second
#define pb push_back
#define pob pop_back
#define endl '\n'
#define fori(s,n) for(int i=s;i<n;i++)
#define forj(s,n) for(int j=s;j<n;j++)
#define int long long
#define ull unsigned long long
#define ll long long
#define ld long double
using namespace std;
using namespace __gnu_pbds;
void solve(){
    int n,q;cin>>n>>q;
    vector<pair<int,int>>sc;
    fori(0,n){
        int l,r;cin>>l>>r;
        sc.pb({l,0});
        sc.pb({r,1});
    }
    vector<int>ans(q,1e9),qq(q);
    fori(0,q) cin>>qq[i];
    sort(all(sc));
    int cnt=0,cntl=0;
    vector<pair<int,int>>xx;
    fori(0,sc.size()){
        auto [x,type]=sc[i];
        if(type==0) cnt++;
        else{
            cnt--;
            cntl++;
        }
        int cntr=n-cnt-cntl;
        if(i==sc.size()-1 || sc[i].fi!=sc[i+1].fi){
            xx.pb({cnt,min(cntl,cntr)});
        }
    }
    sort(rall(xx));
    //for(auto&[x,y]:xx) cout<<x<<' '<<y<<endl;
    int s=xx[0].fi,r=xx[0].se;
    fori(0,q){
        int ost=max(qq[i]-s,0ll);
        int ff=min(ost/2,r);
        ost-=ff*2;
        cout<<ff+ost<<' ';
    }
    cout<<endl;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt=1;
    //cin>>tt;
    while(tt--) solve();
    return 0;
}
