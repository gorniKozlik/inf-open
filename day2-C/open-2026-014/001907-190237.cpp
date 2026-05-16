#include <bits/stdc++.h>

using namespace std;

void solve();

// #include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    //cin>>t;
    while (t--) {
        solve();
    }
    return 0;
}

#define int long long
#define endl '\n'
const int N = 3e5+100, MOD = 998244353, INF = 2e18;
const double EPS = 1e-6, pi = acos(-1);
int add(int a,int b) {
    if (a+b>=MOD)return a+b-MOD;
    return a+b;
}
int sub(int a,int b) {
    if (a-b<0)return a-b+MOD;
    return a-b;
}
int mul(int a,int b) {
    return (a*b)%MOD;
}

struct segm {
    int l,r;
};
struct scl {
    int x,t;
};
bool comp(scl a,scl b) {
    if (a.x==b.x) {
        return a.t>b.t;
    }
    return a.x<b.x;
}
void solve() {
    int n,q;
    cin>>n>>q;
    vector<segm> a(n);
    vector<scl> s;
    map<int,int> mpl,mpr;
    for (int i=0;i<n;i++) {
        cin>>a[i].l>>a[i].r;
        s.push_back({a[i].l,1});
        s.push_back({a[i].r,-1});
        mpl[a[i].l]++;
        mpr[a[i].r]++;
    }
    vector<int> ans(n+2,INF);
    vector<vector<pair<int,int>>> len(n+2);
    vector<int> f(n+2,0);
    ans[0]=0;ans[1]=0;

    sort(s.begin(),s.end(),comp);
    int bal=0,l=0,r=n;
    map<int,int> used;
    deque<int> mns;
    for (int i=0;i<2*n;i++) {
        if (i>0 && s[i-1].x!=s[i].x) {
            l+=mpr[s[i-1].x];
        }
        if (!used[s[i].x]) {
            used[s[i].x]=true;
            r-=mpl[s[i].x];
        }
        if (s[i].t==1) {
            bal++;
        }
        if (l>r) {
            int ost=l-r;
            f[bal]=max(f[bal],r);
            int curr=bal+2*r+1;
            int mnv=min(mpl[s[i].x],ost);
            len[curr].emplace_back(mnv,r+1);
        }else {
            int ost=r-l;
            f[bal]=max(f[bal],l);
            int curr=bal+2*l+1;
            int mnv=min(mpr[s[i].x],ost);
            len[curr].emplace_back(mnv,l+1);
        }
        if (s[i].t==-1) {
            bal--;
        }
    }
    vector<set<pair<int,int>>> val(2);
    for (int i=0;i<=n;i++) {
        int cur=i%2;
        val[cur].insert({-i,i+2*f[i]});
        for (int j=0;j<2;j++) {
            while (!val[j].empty() && val[j].begin()->second<i) {
                val[j].erase(val[j].begin());
            }
        }
        if (!val[cur].empty()) {
            int csum=(i-(-val[cur].begin()->first))/2;
            ans[i]=min(ans[i],csum);
        }
    }
    set<pair<int,int>> vl;
    for (int i=0;i<=n;i++) {
        for (auto [ln,st]:len[i]) {
            vl.insert({-(i-st),i+ln-1});
        }
        while (!vl.empty() && vl.begin()->second<i) {
            vl.erase(vl.begin());
        }
        if (!vl.empty()) {
            int csum=i-(-vl.begin()->first);
            ans[i]=min(ans[i],csum);
        }
    }
    for (int i=n;i>=0;i--) {
        ans[i]=min(ans[i],ans[i+1]);
    }
    while (q--) {
        int k;
        cin>>k;
        if (ans[k]==INF)assert(0);
        cout<<ans[k]<<endl;
    }
}
