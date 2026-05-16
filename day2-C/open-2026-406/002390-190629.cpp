#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define int long long

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<pair<int,int>>line;
    for (int i = 0; i < n; ++i) {
        int l,r;
        cin >> l >> r;
        line.emplace_back(l,1);
        line.emplace_back(r,2);
    }
    sort(line.begin(),line.end());
    int cntl = 0;
    int cntr = 0;
    int lastpos = 0;
    map<int,int>endr;
    int mx = 0;
    int x = 0;
    for (auto [pos,id] : line) {
        if (id == 2) {
            mx = max(mx,cntl - endr[lastpos]);
            if (mx == cntl - endr[lastpos]) {
                x = max(x,min(n - cntl,endr[lastpos]));
            }
            cntr++;
            endr[pos] = cntr;
        }else {
            cntl++;
            endr[pos] = cntr;
            lastpos = pos;
        }
    }
    while (q--){
        int k;
        cin >> k;
        if (k <= mx) {
            cout << 0 << endl;
        }else if (k <= mx + x * 2) {
            cout << (k - mx + 1) / 2 << endl;
        }else {
            cout << (x + (k - mx - x * 2)) << endl;
        }
    }
    return 0;
}
