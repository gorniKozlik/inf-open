#include <bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;
using ld = long double;

const int inf = 1e12;
const int mod = 998244353;


void go() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v1;
    vector<pair<int, int>> v(n);
    vector<int> l;
    vector<int> r;
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        v1.push_back({v[i].first, -1});
        v1.push_back({v[i].second, 1});
        l.push_back(v[i].first);
        r.push_back(v[i].second);
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    sort(v1.begin(), v1.end());
    v1.erase(unique(v1.begin(), v1.end()), v1.end());

    vector<pair<int, pair<int, int>>> dp;
    for (int i = 0; i < n; i++) {
        dp.push_back({v[i].first, {-1, i}});
        dp.push_back({v[i].second, {1, i}});
    }

    for (int i = 0; i < v1.size(); i++) {
        dp.push_back({v1[i].first, {0, i}});
    }

    sort(dp.begin(), dp.end());
    vector<int> c(v1.size());
    vector<pair<int, int>> d;

    int cnt = 0;
    int cnt1 = 0;
    for (auto elem : dp) {
        int i = elem.second.second;
        if (elem.second.first == -1) {
            cnt++;
        } else if (elem.second.first == 0) {
            c[i] = cnt;
        } else {
            cnt--;
        }
    }

    vector<int> ans(n + 2, -1);
    int pos = 1;
    vector<pair<int, pair<int, int>>> z;
    for (int i = 0; i < v1.size(); i++) {
        z.push_back({c[i], v1[i]});
    }

    sort(z.rbegin(), z.rend());
    for (auto elem : z) {
        int y = upper_bound(l.begin(), l.end(), elem.second.first) - l.begin();
        int x = lower_bound(r.begin(), r.end(), elem.second.first) - r.begin();
        y = n - y;
        int mn = min(x, y);
        int o = elem.first + min(x, y) * 2;
        while (pos <= o) {
            int g = (pos - elem.first + 1) / 2;
            ans[pos] = max(g, (int)0);
            pos++;
        }

        x -= mn;
        y -= mn;
        if (elem.second.second == -1 and x != 0) {
            if (pos == o + 1) {
                ans[pos] = mn + 1;
                pos++;
            }
        }

        if (elem.second.second == 1 and y != 0) {
            if (pos == o + 1) {
                ans[pos] = mn + 1;
                pos++;
            }
        }
    }

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
 }

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        go();
    }
}