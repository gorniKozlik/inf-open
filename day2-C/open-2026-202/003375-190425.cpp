#include <bits/stdc++.h>
/*#pragma GCC optimize("O3,unrool-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")*/
#define int long long

using namespace std;
struct node {
    int k,kl,kr,l,r,cnt;
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin >>n >>q;
    vector <pair<int,int>> ev;
    for (int i=0; i<n; ++i) {
        int l,r;
        cin >>l >>r;
        ev.push_back({l,-1});
        ev.push_back({r,1});
    }
    sort(ev.begin(), ev.end());
    int id=0;
    int k=0,kl=0,kr=0,l=0;
    vector <node> al;
    while (id<2*n) {
        int x=ev[id].first;
        int flol=0,flor=0;
        while (id!=2*n && ev[id].first==x) {
            if (ev[id].second==-1) {
                kl++;
                flol++;
            }
            else {
                k--;
                kr++;
                flor++;
            }
            id++;
        }
        al.push_back({k,kl,kr,l, (n-k-kl-kr-l)});
        kl-=flol;
        k+=flol;
        kr-=flor;
        l+=flor;
    }
    sort(al.rbegin(), al.rend(), [](node a, node b) {
        return (a.k+a.kl+a.kr)<(b.k+b.kl+b.kr);
    });
    int inf=1e9+67;
    vector <int> ans(n+1, inf);
    for (auto it: al) {
        k=it.k,kl=it.kl,kr=it.kr,l=it.l;
        int r=it.r;
        int start=k+kl+kr;
        int rig=start+2*min(l,r);
        for (int i=start; i<=start+2*min(l,r); ++i) {
            ans[i]=min(ans[i], (i-start+1)/2);
        }
        int v=min(l,r);
        l-=v,r-=v;
        int cnt=(rig-start)/2;
        int mx=(min(l,kl)+min(r,kr));
        for (int i=rig+1; i<=rig+mx; ++i) {
            ans[i]=min(ans[i], cnt+i-rig);
        }
    }


    while (q--) {
        int x;
        cin >>x;
        cout <<ans[x] <<" ";
    }
}
