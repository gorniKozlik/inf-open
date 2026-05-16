
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ordered_set  = tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()



struct SegTree {
    int inf = 2e13;
    struct Node {
        int sum, mn, mx, lz;
    };
    int n;
    vector<Node> t;
    SegTree(int n) : n(n),  t(n * 4 + 5, {0,0,0,-1}) {}

    void combine(int v, int x, int len) {
        t[v].sum = x * len;
        t[v].mx = x;
        t[v].mn = x;
        t[v].lz = x;
    }

    Node merge(Node a, Node b) {
        Node res;
        res = {a.sum + b.sum, min(a.mn, b.mn), max(a.mx,b.mx), -1};
        return res;
    }

    void push(int v, int l, int r) {
        if (r-l==1||t[v].lz==-1) return;
        int m = (l + r) / 2;
        combine(2*v+1, t[v].lz, m - l);
        combine(2*v+2, t[v].lz, r - m);
        t[v].lz=-1;
    }

    void set(int v, int l, int r, int ql, int qr, int x) {
        if (l >= qr || r <= ql) return;
        if (l >= ql && r <= qr) {
            combine(v, x, r - l);
            return;
        }

        push(v, l, r);
        int m = (l + r) / 2;
        set(2*v+1,l,m,ql,qr,x);
        set(2*v+2,m,r,ql,qr,x);
        t[v] = merge(t[2*v+1], t[2*v + 2]);
    }

    Node query(int v,int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) return {0,inf,-inf,-1};
        if (l >= ql && r <= qr) {
            return t[v];
        }

        push(v, l, r);
        int m = (l + r) / 2;
        return merge(query(2*v+1,l,m,ql,qr), query(2*v+2,m,r,ql,qr));
    }

    int sum(int l,int r) {
        Node ans = query(0,0,n,l,r);
        return ans.sum;
    }
    int mn(int l,int r) {
        Node ans = query(0,0,n,l,r);
        return ans.mn;
    }
    int mx(int l,int r) {
        Node ans = query(0,0,n,l,r);
        return ans.mx;
    }

    void set(int l, int r, int x) {
        set(0,0,n,l,r,x);
    }
};


void solve() {
   int n, q;
   cin >> n >> q;
   
   vector<int> l(n), r(n);
   map<int,int> all, sz;

   for (int i = 0;i < n;i++) {
    cin >> l[i] >> r[i];
    all[l[i]] = all[r[i]] = 1;
   }
   int kl = 0;
   for (auto [el, p] : all) sz[el] = kl++;
   for (auto& el : l) el = sz[el] + 1;
   for (auto& el : r) el = sz[el] + 1;


   int k = 2 * n + 67;


   vector<int> pkr(k, 0);
   for (auto& el : l) pkr[el]++;
   for (auto& el : r) pkr[el]--;
   for (int i = 1;i < k;i++) pkr[i] += pkr[i - 1];


   vector<int> allr(k, 0), alll(k, 0);

   for (auto el : l) alll[el-1]++;
   for (auto el : r) allr[el]++;

   for (int i = 1;i < k;i++) allr[i] += allr[i - 1];
   for (int i=k-2;i>= 0;i--) alll[i] += alll[i + 1];
   


    SegTree ans(k);
    ans.set(0, k, 0);

    vector<pair<int,pair<int,int> > > put;

    for (int i = 0;i < k;i++) {
        int t = pkr[i];
        int can = min(alll[i], allr[i]);

        put.push_back({t, {t, min(k, t + can * 2 + 1)}});
    }

    sort(put.begin(), put.end());

    for (auto [x, lr] : put) {
        auto [l, r] = lr;


        ans.set(l, r, x);
    }


  
  while (q--) {
    int x;
    cin >> x;

    int in = ans.sum(x,x + 1);

    cout << (x - in + 1) / 2 << '\n';
  }
   
   
}

signed main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    //  cin >> t;
    while (t --> 0) solve();
}
