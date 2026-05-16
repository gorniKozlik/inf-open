//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std;
//#pragma GCC optimize("O3,Ofast,unroll-loops")
//#pragma GCC target("avx2,avx,bmi")
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// using ordered_set  = tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

mt19937 rnd(503462350);



signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int inf = 1e13;


    int n;
    cin >> n;
    int q; cin >> q;
    vector<vector<int>>ev;
    for(int i=0;i<n;++i) {
        int l, r;
        cin>>l>>r;
        ev.push_back({l,-1,i});
        ev.push_back({l,0});
        ev.push_back({r,1,i});
        ev.push_back({r,0});
    }
    int ns = n, st = 0;
    vector<vector<int>>que(q);
    for(int i=0;i<q;++i) {
        que[i].resize(2);
        cin>>que[i][0];
        que[i][1]=i;
    }
    vector<int>ans(n + 1,inf);
    sort(ev.begin(), ev.end());
    vector<vector<int>>t2add(n+5),t2del(n+5),t3(n+5);
    int mxz = 0;
    int cur = 0;
    for(auto &e : ev) {
        int type = e[1];
        if (type == -1) {
            ns--;
            cur++;
        } else if (type == 1) {
            st++;
            cur--;
        } else {
            int alr = cur;
            int br = ns;
            int bl = st;
            mxz = max(mxz, alr);
            t2add[alr+1].push_back(alr);
            int dbl = min(bl, br);
            t2del[alr+1+2*dbl].push_back(alr);
            t3[alr+2*dbl+1].push_back(dbl+alr);
        }
    }
    for(int i=1;i<=mxz;++i) ans[i]=0;
    multiset<int>cs;
    for(int i=1;i<=n;++i) {
        for(auto p : t2add[i]) cs.insert(p);
        for(auto p:t2del[i]) cs.erase(cs.find(p));
        if (!cs.empty()) {
            ans[i]=min(ans[i], (i-*cs.rbegin()+1)/2);
        }
    }
    cs = {};
    for(int i=1;i<=n;++i) {
        for(auto p : t3[i]) cs.insert(p);
        if (!cs.empty()) {
            ans[i]=min(ans[i], i-*cs.rbegin());
        }
    }
    for(int i=0;i<q;++i) {
        cout<<ans[que[i][0]]<<' ';
    }
}



