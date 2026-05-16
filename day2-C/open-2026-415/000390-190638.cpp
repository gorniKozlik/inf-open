#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve();

signed main() {
#ifdef openol
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t=1;
    //cin>>t;
    while (t--) solve();
}

void solve(){
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>> a;
    for (int i=0;i<n;i++) {
        int l,r;
        cin>>l>>r;
        a.push_back({l,-1});
        a.push_back({r,1});
    }
    sort(a.begin(),a.end());
    int op=0,cl=0;
    vector<pair<int,int>> v;
    for (int i=0;i<2*n;i++) {
        auto p=a[i];
        if (p.second==-1) op++;
        else cl++;
        int pok=op-cl;
        int l=cl;
        int r=n-l-pok;
        v.push_back({pok,pok+2*min(l,r)});
    }
    vector<int> qu(q);
    for (int i=0;i<q;i++) cin>>qu[i];
    vector<vector<int>> b;
    for (auto i:v) {
        b.push_back({i.first,-1});
        b.push_back({i.second,1,i.first});
    }
    for (int i=0;i<q;i++){
        b.push_back({qu[i],0,i});
    }
    sort(b.begin(),b.end());
    multiset<int,greater<>> st;
    int ans[q];
    for (auto i:b) {
        if (i[1]==-1) st.insert(i[0]);
        if (i[1]==1) st.erase(st.find(i[2]));
        if (i[1]==0) ans[i[2]]=(i[0]-*st.begin()+1)/2;
    }
    for (auto i:ans) cout<<i<<' ';
}