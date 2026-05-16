#ifndef local
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using str = string;
using ordset = tree<ll,null_type, less<>,rb_tree_tag, tree_order_statistics_node_update>;
using hashmap = gp_hash_table<ll,ll>;
using hashset = gp_hash_table<ll, null_type>;

auto sd = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(sd);
const ll mod = 998244353;
ll ps[1ll<<20];
ll d[1ll<<20];
const ll inf=  2e9;
void push(ll v) {
    if (ps[v]==inf) {
        return;
    }
    d[v*2]=min(d[v*2], ps[v]);
    d[v*2+1]=min(d[v*2+1], ps[v]);
    ps[v*2]=min(ps[v*2],ps[v]);
    ps[v*2+1]=min(ps[v*2+1], ps[v]);
    ps[v] = inf;
}
void build(ll v, ll l, ll r) {
    if (r-l<= 1) {
        d[v] = inf;
        ps[v] = inf;
        return;
    }
    build(v*2, l, (l+r)>>1);
    build(v*2+1, (l+r)>>1, r);
    d[v] = min(d[v*2],d[v*2+1]);
    ps[v]=inf;
}
void upd(ll v, ll l ,ll r, ll sl, ll sr, ll A) {
    push(v);
    if (sl <= l &&r  <= sr) {
        d[v] =min(d[v],A);
        ps[v]=min(ps[v],A);
        push(v);
        return;
    }
    else if (sr <= l || r <= sl) {
        return;
    }
    upd(v*2, l, (l+r)>>1, sl,sr,A);
    upd(v*2+1, (l+r)>>1, r, sl,sr,A);
    d[v]=min(d[v*2],d[v*2+1]);
}
ll get_ans(ll v, ll l, ll r, ll sl, ll sr) {
    push(v);
    if (sl <= l && r <= sr) return d[v];
    else if (sr <= l || r <= sl) {
        return inf;
    }
    return min(get_ans(v*2, l, (l+r)>>1, sl,sr),get_ans(v*2+1, (l+r)>>1, r,sl,sr));
}
void sol() {
    ll n, q;
    cin>>n>>q;
    vector<pll>a;
    deque<pll> rg;
    deque<pll> lf;
    vector<ll> points;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin>>l>>r;
        a.emplace_back(l, r);
        points.emplace_back(l);
        points.emplace_back(r);
    }
    sort(a.begin(), a.end());
    set<pll> cur;
    for (auto u: a) {
        rg.emplace_back(u);
    }
    deque<pll> ans(n);
    for (int j = 0; j < q; j++) {
        cin>>ans[j].first;
        ans[j].second=j;
    }build(1, 0, q);
    sort(ans.begin(), ans.end());
    sort(points.begin(), points.end());
    vector<vector<ll>> p;
    for (auto X: points) {
        while (!rg.empty()&&rg.front().first<= X) {
            cur.insert({rg.front().second, rg.front().first});
            rg.pop_front();
        }
        while (!cur.empty()&&cur.begin()->first < X) {
            lf.emplace_back(*cur.begin());
            cur.erase(cur.begin());
        }
        ll L = lf.size(); ll R = rg.size();
        ll CUR = cur.size();
        pll yy=  make_pair(CUR, 1e9);
        ll res = CUR+2*min(L,R);
        ll ost = abs(R-L);
        p.push_back({CUR, min(L,R), ost});

    }   sort(p.rbegin(), p.rend());
    ll mn_lr = p[0][1];
    ll CUR=p[0][0];
    pll yy=  make_pair(CUR, 1e9);
    ll res = CUR+2*mn_lr;
    ll ost = p[0][2];
    for (int j = 0; j <= mn_lr; j++) {
        yy.first=CUR+2*j;
        ll Y = lower_bound(ans.begin(), ans.end(), yy)-ans.begin()-1;
        upd(1, 0, n, 0, min(n, Y+1),j);
        if (Y+1==n) {
            break;
        }
    }
    for (int j = 1; j <= ost; j++) {
        yy.first=res+j;
        ll Y = lower_bound(ans.begin(), ans.end(), yy)-ans.begin()-1;
        upd(1, 0, n, 0, min(n, Y+1),mn_lr+j);
        if (Y+1==n) {
            break;
        }
    }
    vector<ll> answ(q);
    for (int i = 0; i < q; i++) {
        answ[ans[i].second]=get_ans(1, 0, n, i, i+1);
    }
    for (auto ww: answ)cout<<ww<<" ";
}

signed main() {
    cout<<fixed<<setprecision(19);
#ifdef local
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll tt = 1;
    //cin>>tt;
    while (tt--) {
        sol();
    }
}