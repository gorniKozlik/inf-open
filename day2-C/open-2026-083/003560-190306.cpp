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
    sort(que.begin(), que.end());
    vector<int>ans(q, inf);
    sort(ev.begin(), ev.end());
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
            for(int i = 0; i < q; ++i) {
                int x = que[i][0];
                if (x <= alr) ans[i] = min(ans[i], 0LL);
                else {
                    int dbl = min(bl, br);
                    if (x <= alr + 2 * dbl) {
                        ans[i] = min(ans[i], (x-alr+1)/2);
                    } else {
                        x -= alr ;
                        x -= 2 * dbl;
                        ans[i] = min(ans[i], dbl + x);
                    }
                }
            }
        }
    }
    vector<int>res(q);
    for(int i=0;i<q;++i) {
        res[que[i][1]]=ans[i];
    }
    for(auto x:res)cout<<x<<' ';
}



