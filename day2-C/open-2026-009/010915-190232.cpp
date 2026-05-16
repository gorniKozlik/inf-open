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
using ll = int;
using ld = long double;
using pll = pair<ll,ll>;
using str = string;
using ordset = tree<ll,null_type, less<>,rb_tree_tag, tree_order_statistics_node_update>;
using hashmap = gp_hash_table<ll,ll>;
using hashset = gp_hash_table<ll, null_type>;

auto sd = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(sd);
const ll mod = 998244353;
bool cmp(pll a, pll b) {
    return a.second<b.second;
}
const ll inf=  2e9;
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
    deque<pll> ans(q);
    for (int j = 0; j < q; j++) {
        cin>>ans[j].first;
        ans[j].second=j;
    }
    sort(ans.begin(), ans.end());
    sort(points.begin(), points.end());
    map<ll,ll> pp;
    map<ll, ll> pp1;
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
        pp[-CUR]=max(pp[-CUR],min(L,R));
        pp1[-min(L,R)]=max(pp1[-min(L,R)], CUR);
    }
    vector<pll> T;
    for (auto [u,v]:pp) {
        T.emplace_back(-u, v);
    }
    vector<pll> T1;
    for (auto [u,v]:pp1) {
        T1.emplace_back(v, -u);
    }
   // sort(T1.rbegin(),T1.rend(), cmp);
    vector<ll> answ(q,inf);
    for (int j = 0; j < q; j++) {
        ll k = ans[j].first;
        ll id = ans[j].second;
        ll cnt_op = 100000000/q;
        for (auto [sz, mlr]: T) {
            cnt_op--;
            if ((sz) >= k) {
                answ[id]=0;
            }
            else if (k-sz <= 2*mlr) {
                answ[id] =min(answ[id], (k-sz)/2+(k-sz)%2);
            } else {
                ll cost= mlr;
                ll O = k-sz-2*mlr;
                answ[id]=min(answ[id],cost+O);
            }
            if (cnt_op==0)break;
        }cnt_op = 100000000/q;
        for (auto [sz, mlr]:T1) {
            cnt_op--;
            if ((sz) >= k) {
                answ[id]=0;
            }
            else if (k-sz <= 2*mlr) {
                answ[id] =min(answ[id], (k-sz)/2+(k-sz)%2);
            } else {
                ll cost= mlr;
                ll O = k-sz-2*mlr;
                answ[id]=min(answ[id],cost+O);
            }
            if (cnt_op==0)break;
        }
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