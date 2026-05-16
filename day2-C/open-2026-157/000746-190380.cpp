#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 3, mod = 998244353, inf = 1e18 + 7;
int tree[4 * N];
int d[4 * N];
void push(int v){
    tree[2 * v + 1] += d[v];
    tree[2 * v + 2] += d[v];
    d[2 * v + 1] += d[v];
    d[2 * v + 2] += d[v];
    d[v] = 0;
}
void add(int v, int l, int r, int ql, int qr, int t){
    if (ql <= l && r <= qr){
        tree[v] += t;
        d[v] += t;
        return;
    }
    if (l > qr || ql > r){
        return;
    }
    push(v);
    int m = (l + r) / 2;
    add(2 *  v+ 1, l, m, ql,qr, t);
    add(2 * v + 2, m + 1, r, ql, qr, t);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}
int res[N];
pair<int, int> ot[N];
signed  main(){
     ios::sync_with_stdio(false);
     cin.tie(nullptr);
     int n, q;
     cin >> n >> q;
     vector<int> all;
     set<pair<int, int>> rig, lef;
     for (int i = 1; i <= n + 1; i++){
        res[i] = n;
     }
     for (int i = 0 ;i < n; i++){
        res[i + 1] = inf;
        int x, y;
        cin >> x >> y;
        all.push_back(x);
        all.push_back(y);
        rig.insert({y, x});
        lef.insert({x, y});
        ot[i] = {x, y};
     }
     sort(all.begin(), all.end());
     map<int, int> ind;
     for (int i = 0 ;i < all.size(); i++){
        ind[all[i]] = i;
     }
     for (int i = 0; i < n; i++){
        add(0, 0, 2 * n - 1, ind[ot[i].first], ind[ot[i].second], 1);
     }
     int cur = 0;
     while (true){
        int mx = tree[0];
        res[mx]  =cur;
        if (mx == n){
            break;
        }
        auto [r1, l1] = *rig.begin();
        rig.erase({r1, l1});
        lef.erase({l1, r1});
        auto [l2, r2] = *(--lef.end());
        lef.erase({l2, r2});
        rig.erase({r2, l2});
        //cout << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
        add(0, 0, 2 * n - 1, ind[r1], ind[l2], 1);
        if (ind[r1] + 1 <= ind[l2] - 1){
            add(0, 0, 2 * n - 1, ind[r1] + 1, ind[l2] - 1, 1);
        }
        cur++;
        lef.insert({l1, r2});
        rig.insert({r2, l1});
        lef.insert({r1, l2});
        rig.insert({l2, r1});
     }
     for (int i = n; i >= 1; i--){
        res[i] = min(res[i], res[i + 1]);
     }
     while (q--){
        int k;
        cin >> k;
        cout << res[k] << " ";
     }
 }

