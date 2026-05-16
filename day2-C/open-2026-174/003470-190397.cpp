#include <bits/stdc++.h>
using namespace std;
#define int long long
//using namespace __gnu_pbds;
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    
    vector<int> b;
    map<int, int> ind;
    for (auto e : a) {
        b.push_back(e.first);
        b.push_back(e.second);
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++) {
        ind[b[i]] = i;
    }
    //cout << "e" << endl;
    vector<int> no(2 * n, 0);
    vector<pair<int, int>> plus(2 * n, {0, 0});
    for (auto e : a) {
        plus[ind[e.first]].first += 1;
        plus[ind[e.second]].second += 1;
    }
    vector<int> ans(n, -1);
    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        //cout << i << " " << plus[i].first << " " << plus[i].second << endl;
        cnt += plus[i].first;
        no[i] = cnt;
        cnt -= plus[i].second;
    }


    vector<int> aa(2 * n);
    for (int i = 0; i < n; i++) {
        aa[i] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        aa[2 * n - 1 - i] = i + 1;
    }

    vector<pair<int, int>> sv;
    for (int i = 0; i < 2 * n; i++) {
        sv.push_back({no[i], aa[i]});
    }

    
    sort(sv.rbegin(), sv.rend());
    int j = 0;
    for (auto e : sv) {
        //cout << e.first << " " << e.second << endl;
        for (;j < e.second; j++) {
            ans[j] = max(0ll, (j - e.first + 2) / 2);
        }
    }
    
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x - 1] << " ";
    
    }
    cout << endl;
}