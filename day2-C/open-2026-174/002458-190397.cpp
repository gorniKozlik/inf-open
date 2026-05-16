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
    int j = 0;
    for (int i = 0; i < 2 * n; i++) {
        //cout << i << " " << plus[i].first << " " << plus[i].second << endl;
        cnt += plus[i].first;
        while (j < cnt) {
            ans[j] = 0;
            j += 1;
        }
        no[i] = cnt;
        cnt -= plus[i].second;
    }

    /*
    for (auto e : no) {
        cout << e << " ";
    }
    cout << endl;
    for (auto e : ans) {
        cout << e << " ";
    }
    cout << endl;*/


    vector<pair<int, int>> left, right;
    for (auto e : a) {
        if (ind[e.second] < n) {
            left.push_back({ind[e.first], ind[e.second]});
        }
        if (ind[e.first] >= n) {
            right.push_back({ind[e.first], ind[e.second]});
        }
    }
    //cout << left.size() << " " << right.size() << endl;
    sort(left.begin(), left.end());
    sort(right.rbegin(), right.rend());
    cnt = j;
    for (int i = 0; i < left.size(); i++) {
       // cout << left[i].second << " " << right[i].first << endl;
        for (int k = left[i].second ; k <= right[i].first; k++) {
            no[k] += 1;
            if (k > left[i].second && k < right[i].first) {
                no[k] += 1;
            }
            cnt = max(no[k], cnt);
        }
        //cout << "ok" << cnt << endl;
        while (j < cnt && j < ans.size()) {
            ans[j] = i + 1;
            j += 1;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x - 1] << " ";
    
    }
    cout << endl;
}