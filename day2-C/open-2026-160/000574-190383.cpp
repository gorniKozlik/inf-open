#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define all(v) v.begin(),v.end()

void fast_in_out() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
}

const ll N=2e5+10,INF=1e18;

vector<pair<ll,ll>> v;
ll l[N],r[N],ans[N];

int main() {
    fast_in_out();
    ll n,q,i,a,b,k;
    cin >> n >> q;
    for (i=0;i<=n;i++)ans[i]=INF;
    map<ll,ll> mp;
    for (i=1;i<=n;i++) {
        cin >> l[i] >> r[i];
        mp[l[i]]=1;
        mp[r[i]]=1;
    }
    ll cnt=1;
    for (auto &u:mp)u.second=cnt++;
    for (i=1;i<=n;i++) {
        l[i]=mp[l[i]];
        r[i]=mp[r[i]];
        v.push_back({l[i],1});
        v.push_back({r[i]+1,-1});
    }
    sort(v.begin(),v.end());
    vector<pair<pair<ll,ll>,ll>> vc,vc1;
    ll cnt1=0,cnt2=0,j;
    cnt=0;
    for (j=0,i=1;i<=2*n+1;i++) {
        while (j<v.size() && v[j].first<=i) {
            cnt1+=v[j].second==-1;
            cnt+=v[j].second;
            j++;
        }
        a=cnt1;
        b=n-cnt1-cnt;
        vc.push_back({{cnt,cnt},1});
        vc.push_back({{cnt+2*min(a,b)+1,cnt},-1});
        vc1.push_back({{cnt+2*min(a,b)+1,cnt+min(a,b)},1});
    }
    multiset<ll> s;
    sort(vc.begin(),vc.end());
    sort(vc1.begin(),vc1.end());
    for (i=0,j=0;i<=n;i++) {
        while (j<vc.size() && vc[j].first.first<=i) {
            if (vc[j].second==1) {
                s.insert(vc[j].first.second);
            }else {
                s.erase(s.find(vc[j].first.second));
            }
            j++;
        }
        if (s.size()>0) {
            ans[i]=min(ans[i],(i-*s.rbegin()+1)/2);
        }
    }
    s.clear();
    for (i=0,j=0;i<=n;i++) {
        while (j<vc1.size() && vc1[j].first.first<=i) {
            s.insert(vc1[j].first.second);
            j++;
        }
        if (s.size()>0) {
            ans[i]=min(ans[i],i-*s.rbegin());
        }
    }
    for (i=n-1;i>=0;i--)ans[i]=min(ans[i],ans[i+1]);
    while (q--) {
        cin >> a;
        cout << ans[a] << " ";
    }
    return 0;
}