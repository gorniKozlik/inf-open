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
    int z = 0;
    vector<int> ans(n + 3, 1e16);
    for (int i = 0; i < 2*n ;++i) {
        auto [t, fl] = vv[i];
        if (fl == 0) col++;
        else {
            col--;
            z++;
        }
        st.insert({-col, t});
        mx = max(mx, col);
        int sl = n - z - col;
        int sm = col + min(sl, z)*2;
        ans[sm] = min(ans[sm], min(sl, z));
    }
    vector<int> res(n + 1, 0);
    int mx1 = 1e16;
    int mx2 = 1e16;
    for (int i = n; i > 0; --i) {
        if (i % 2 == 1) mx1 = max(0LL, mx1-1);
        else mx2 = max(0LL, mx2 - 1);
        res[i] = min({ans[n], mx1, mx2});
        if (i % 2 == 1) {
            mx2 = min(mx2, ans[i]);
        } else {
            mx1 = min(mx1, ans[i]);
        }
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << res[k] <<  " ";
    }
    return 0;
}