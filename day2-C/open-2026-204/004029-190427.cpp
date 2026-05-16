
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using ordered_set  = tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()



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
   

   if (n * n > 1e7) {
    while (q--) {
        int x;
        cin >> x;
        cout <<(x + 1) / 2 << '\n';
    }
    return ;
   }


    vector<int> ans(k, n);
   for (int i = 0;i < k;i++) {
    int t = pkr[i];
    int can = min(alll[i], allr[i]);
    for (int j = 0;j <= can;j++) {
        ans[t + 2 * j] = min(ans[t + 2 * j], j);
        if (t > 0 or j > 0) ans[t-1 + 2 * j] = min(ans[t-1 + 2 * j], j);
    }
   }

  
  while (q--) {
    int x;
    cin >> x;


    

    cout << ans[x] << '\n';
  }
   
   
}

signed main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    //  cin >> t;
    while (t --> 0) solve();
}
