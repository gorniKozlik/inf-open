#include <bits/stdc++.h>
using innt = int;
#define int long long
using namespace std;

bool cmp(pair<int, int> &a, pair<int, int> &b) {
    return a.first < b.first;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> lr;
    set<int> a;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        lr.push_back({l, r});
        a.insert(l);
        a.insert(r);
    }
    sort(lr.begin(), lr.end(), cmp);
    unordered_map<int, int> mp;
    int it = 0;
    for (auto el : a) {
        mp[el] = it++;
    }
    for (int i = 0; i < n; ++i) {
        lr[i] = {mp[lr[i].first], mp[lr[i].second]};
    }
    vector<pair<int, int>> vv;
    for (auto [l, r] : lr) {
        vv.push_back({l, 0});
        vv.push_back({r, 1});
    }
    sort(vv.begin(), vv.end());
    set<pair<int, int>> st;
    int col = 0;
    int mx = 0;
    for (int i = 0; i < 2*n ;++i) {
        auto [t, fl] = vv[i];
        if (fl == 0) col++;
        else col--;
        st.insert({-col, t});
        mx = max(mx, col);
    }
    if (mx == 1) {
        for (int i = 0; i < q; ++i) {
            int k;
            cin >> k;
            cout << k/2 << " ";
        }
    }
    return 0;
}