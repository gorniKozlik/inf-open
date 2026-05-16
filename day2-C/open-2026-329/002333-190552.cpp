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
    vector<int>qq(q),ans(n+1,1e9);
    fori(0,q) cin>>qq[i];
    sort(all(sc));
    int cnt=0,cntl=0;
    vector<vector<int>>upd(3*n+1),del(3*n+1);
    fori(0,sc.size()){
        auto [x,type]=sc[i];
        if(type==0) cnt++;
        else{
            cnt--;
            cntl++;
        }
        int cntr=n-cnt-cntl;
        if(i==sc.size()-1 || sc[i].fi!=sc[i+1].fi){
           int zz=min(cntl,cntr);
           upd[cnt].pb(cnt/2);
           del[cnt+zz*2].pb(cnt/2);
        }
    }
    multiset<int>st;
    for(int i=0;i<=n;i+=2){
        for(auto&x:upd[i]) st.insert(-1*x);
        if(!st.empty()){
            ans[i]=min(ans[i],i/2+(*st.begin()));
        }
        for(auto&x:del[i]) st.erase(st.find(-1*x));
    }
    st.clear();
    for(int i=1;i<=n;i+=2){
        for(auto&x:upd[i]) st.insert(-1*x);
        if(!st.empty()){
            ans[i]=min(ans[i],i/2+(*st.begin()));
        }
        for(auto&x:del[i]) st.erase(st.find(-1*x));
    }
    fori(1,n+1) ans[i]=min(ans[i],ans[i-1]+1);
    for(int i=n-1;i>=0;i--) ans[i]=min(ans[i],ans[i+1]);
    for(auto&x:qq) cout<<ans[x]<<' ';
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
