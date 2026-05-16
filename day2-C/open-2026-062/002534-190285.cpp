#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using V = vector<ll>;
using VV = vector<V>;
using VVV = vector<VV>;
using VVVV = vector<VVV>;
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VVVP = vector<VVP>;
using VB = vector<bool>;
using VVB = vector<VB>;
#define Alexander_Babin int main()
#define Philipp_Gribov void solve()
#define Vorg_Cup void build()
#define Ivan_Argunov ull binpow(ull a, ull n)

mt19937 rnd('zalupa');
const ull base = 83;
const ull mod = 998244353;
Ivan_Argunov {
    ull ans = 1;
    while (n) {
        if (n&1) ans = ans * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ans;
}
ull pows[1000001];
ull rpows[1000001];
ull fact[1000001];
ull rfact[1000001];
Vorg_Cup {
    pows[0] = 1;
    rpows[0] = 1;
    fact[0] = 1;
    rfact[0] = 1;
    for (int i=1;i<=1000000;i++) {
        pows[i] = pows[i-1] * base;
        fact[i] = fact[i-1] * i;
        //pows[i] = pows[i-1] * base % mod;
        //rpows[i] = binpow(pows[i], mod-2);
        //fact[i] = fact[i-1] * i % mod;
        //rfact[i] = binpow(fact[i], mod-2);
    }
}

struct sparse_table {
    int n;
    V a;
    VV sparses;
    void init(V _a){
        a = _a;
        n = _a.size();
        sparses.assign(__lg(n)+1,V(n));
        sparses[0] = _a;
        for (int j=1;j<=__lg(n);j++)
            for (int i=0;i+(1<<j)-1<n;i++)
                sparses[j][i]=min(sparses[j-1][i],sparses[j-1][i+(1<<(j-1))]);
    }
    int get(int l, int r) {
        int x = __lg(r-l+1);
        return min(sparses[x][l],sparses[x][r-(1<<x)+1]);
    }
};

struct furry_tree {
    int n;
    V a;
    V val;
    void upd(int i, int x) {
        for (;i<=n;i+=i&(-i))
            val[i]+=x;
    }
    void init(int _n) {
        n = _n;
        a.assign(n,0);
        val.assign(n+1,0);
    }
    // void init(V _a) {
    //     a = _a;
    //     n = _a.size();
    //     val.assign(n+1,0);
    //     for (int i=0;i<n;i++)
    //         upd(i+1,a[i]);
    // }
    int gett(int r) {
        int ans = 0;
        for (;r>0;r-=r&(-r))
            ans+=val[r];
        return ans;
    }
    int get(int l, int r) {
        return gett(r+1)-gett(l);
    }
};

// int m;
// vector<unordered_map<int,int>> big_furry_tree;
//
// void upd(int i, int j, int x) {
//     for (;i<=m;i+=i&-i) {
//         for (;j<=m;j+=j&-j) {
//             if (!big_furry_tree[i].count(j))
//                 big_furry_tree[i][j]=0;
//             big_furry_tree[i][j]+=x;
//         }
//     }
// }
//
// int get(int ri, int rj) {
//     int ans=0;
//     for (;ri>0;ri-=ri&-ri)
//         for (;rj>0;rj-=rj&-rj)
//             if (big_furry_tree[ri].count(rj))
//                 ans+=big_furry_tree[ri][rj];
// }

int m;
// VV fenwick;
//
// void add(int i, int j) {
//     for (;i<=m;i+=i&-i)
//         fenwick[i].push_back(j);
// }
//
// int get(int i, int j) {
//     int ans=0;
//     for (;i>0;i-=i&-i)
//         ans+=lower_bound(fenwick[i].begin(),fenwick[i].end(),j)-fenwick[i].begin();
//     return ans;
// }

V segtree;
V lz;

void push(int u) {
    lz[2*u+1]+=lz[u];
    lz[2*u+2]+=lz[u];
    segtree[2*u+1]+=lz[u];
    segtree[2*u+2]+=lz[u];
    lz[u]=0;
}

void upd(int l, int r, int x, int u=0, int tl=0, int tr=m-1) {
    if (tr<l or r<tl) return;
    if (l<=tl and tr<=r) {
        segtree[u]+=x;
        lz[u]+=x;
        return;
    }
    int tm=(tl+tr)/2;
    push(u);
    upd(l,r,x,2*u+1,tl,tm);
    upd(l,r,x,2*u+2,tm+1,tr);
    segtree[u]=max(segtree[2*u+1],segtree[2*u+2]);
}

Philipp_Gribov {
    int n,q; cin >> n >> q;
    VP a(n); for (auto &x:a) cin >> x.first >> x.second;
    V b;
    for (int i=0;i<n;i++) {
        b.push_back(a[i].first);
        b.push_back(a[i].second);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for (auto &x:a) {
        x.first=lower_bound(b.begin(),b.end(),x.first)-b.begin();
        x.second=lower_bound(b.begin(),b.end(),x.second)-b.begin();
    }
    m = b.size();
    // fenwick.resize(m+1);
    // for (int i=0;i<n;i++)
    //     upd(a[i].first,m-a[i].second-1);
    // for (auto &x:fenwick)
    //     sort(x.begin(),x.end());
    segtree.resize(4*m);
    lz.resize(4*m);
    for (int i=0;i<n;i++)
        upd(a[i].first,a[i].second,1);
    V ans;
    ans.push_back(segtree[0]);
    set<P> s1,s2;
    VB used(n);
    for (int i=0;i<n;i++) {
        s1.emplace(-a[i].first,i);
        s2.emplace(a[i].second,i);
    }
    while (!s1.empty() and !s2.empty()) {
        P cur_r = *s1.begin(); s1.erase(s1.begin());
        P cur_l = *s2.begin(); s2.erase(s2.begin());
        cur_r.first=-cur_r.first;
        if (cur_l.first+1>cur_r.first-1) break;
        used[cur_l.second]=true;
        used[cur_r.second]=true;
        upd(cur_l.first+1,cur_r.first-1,2);
        ans.push_back(segtree[0]);
        while (!s1.empty() and used[s1.begin()->second])
            s1.erase(s1.begin());
        while (!s2.empty() and used[s2.begin()->second])
            s2.erase(s2.begin());
    }
    while (q--) {
        int x; cin >> x;
        cout << lower_bound(ans.begin(),ans.end(),x)-ans.begin() << '\n';
    }
    // m = b.size();
    // set<P> s_l,s_r;
    // for (int i=0;i<n;i++) {
    //     s_l.emplace(a[i].first,i);
    //     s_r.emplace(a[i].second,i);
    // }
    // int cur_ans=0;
    // {
    //     auto it1=s_r.begin();
    //     for (auto it2=s_r.)
    // }
}

Alexander_Babin {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
}
