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
    for (auto z=last+1; z<=2*n; ++z) {
        s[z]=cnt;
        l[z]=g;
        r[z]=n-g-cnt;
    }
    for (auto i=0; i<q; ++i) {
        int k;
        cin>>k;
        int ans=n;
        for (auto j=0; j<=2*n; ++j) {
            if (s[j]>=k) {
                ans=0;
                break;
            }
            if (min(l[j],r[j])*2+s[j]>=k) ans=min(ans, (k-s[j]-1)/2+1);
            else ans=min(ans, (k-s[j]-2*min(l[j],r[j]))+min(l[j],r[j]));
        }
        cout<<ans<<' ';
    }
}
