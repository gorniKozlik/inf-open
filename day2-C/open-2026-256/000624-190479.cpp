#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long

using namespace __gnu_pbds;
using namespace std;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int cl(vector<pair<int, int>> a) {
    vector<pair<int, int>> ev;
    for (auto x : a) {
        ev.push_back({x.first, 1});
        ev.push_back({x.second, 0});
    }
    sort(ev.begin(), ev.end());
    int cl = 0;
    int mx = 0;
    for (auto x : ev) {
        if (x.second == 0) cl--;
        else cl++;
        mx = max(mx, cl);
    }
    return mx;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    set<int> s;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        s.insert(a[i].first);
        s.insert(a[i].second);
    }
    int cr = 1;
    map<int, int> mp;
    vector<int> l_;
    for (auto x : s) {
        l_.push_back(x);
    }
    for (auto x : l_) {
        mp[x] = cr++;
    }
    for (int i = 0; i < n; ++i) {
        a[i].first = mp[a[i].first];
        a[i].second = mp[a[i].second];
    }
    
    vector<int> cl_(n + 1, 1e9);
    int sm = 0;

    while (true) {
        int now = cl(a);
        for (int i = 0; i <= now; ++i) {
            cl_[i] = min(cl_[i], sm);
        }
        sm++;
        int in_l = 0, in_r = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i].second < a[in_l].second) in_l = i;
            if (a[i].first > a[in_r].first) in_r = i;
        }
        if (a[in_l].second > a[in_r].first) break;
        swap(a[in_l].second, a[in_r].first);
    }
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << cl_[x] << '\n';
    }
}