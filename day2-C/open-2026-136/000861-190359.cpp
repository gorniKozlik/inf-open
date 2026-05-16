#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using lll=__int128;

#ifdef LOCAL
#define deb(x) cout<<__LINE__<<": "<<(#x)<<" = "<<(x)<<endl;
#else
#define deb(x)
#endif
#define all(x) x.begin(), x.end()
#define arr(x) x.rbegin(), x.rend()
#define int ll
constexpr int MAX_N=3e5, INF=1e9;
int t[2][4*MAX_N];

void add(int p, int l, int r, int ql, int qr, int v, int pos) {
    if (l>=qr || r<=ql) return;
    if (ql<=l && r<=qr) {
        t[pos][p]=max(t[pos][p],v);
        return;
    }
    int m=(l+r)/2;
    add(p*2+1, l, m, ql, qr, v, pos);
    add(p*2+2, m, r, ql, qr, v, pos);
}
int get(int p, int l, int r, int in, int pos,int g) {
    if (in>=r || in<l) return -INF;
    if (l+1==r) return max(g,t[pos][p]);
    int m=(l+r)/2;
    g=max(g,t[pos][p]);
    return max(get(p*2+1,l,m,in,pos,g),get(p*2+2,m,r,in,pos,g));
}
signed main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>> a;
    vector<int> s(n*2+1),l(2*n+1),r(2*n+1);
    vector<pair<int,int>> z;
    vector<int> d;
    for (auto i=0; i<n; ++i) {
        int l,r;
        cin>>l>>r;
        z.push_back({l,r});
        d.push_back(l);
        d.push_back(r);
    }
    sort(all(d));
    for (auto& [l,r]: z) {
        l=lower_bound(all(d),l)-d.begin();
        r=lower_bound(all(d),r)-d.begin();
        a.push_back({l,-1});
        a.push_back({r,1});
    }
    sort(all(a));
    int cnt=0,g=0,last=-1;
    for (auto [i,j]: a) {
        for (auto z=last+1; z<i; ++z) {
            s[z]=cnt;
            l[z]=g;
            r[z]=n-g-cnt;
        }   
        last=i-1;
        cnt-=j;
        if (j==1) g++;
    }
    fill(t[0], t[0]+MAX_N*4, -INF);
    for (auto z=last+1; z<=2*n; ++z) {
        s[z]=cnt;
        l[z]=g;
        r[z]=n-g-cnt;
    }
    vector<int> ans(n+1);
    int h=*max_element(all(s));
    for (auto i=0; i<=2*n; ++i) {
        add(0,0,n+1,h,min(l[i],r[i])*2+s[i]+1,s[i]-1,0);
        add(0,0,n+1,min(l[i],r[i])*2+s[i]+1,n+1,s[i]+min(l[i],r[i]),1);
    }
    for (auto i=h+1; i<=n; ++i) {
        ans[i]=min((i-get(0,0,n+1,i,0,-INF))/2,i-get(0,0,n+1,i,1,-INF));
    }
    for (auto i=0; i<q; ++i) {
        int k;
        cin>>k;
        cout<<ans[k]<<' ';
        // int ans=n;
        // for (auto j=0; j<=2*n; ++j) {
        //     if (s[j]>=k) {
        //         ans=0;
        //         break;
        //     }
        //     if (min(l[j],r[j])*2+s[j]>=k) ans=min(ans, (k-s[j]-1)/2+1);
        //     else ans=min(ans, k-s[j]-min(l[j],r[j]));
        // }
        // cout<<ans<<' ';
    }
}
