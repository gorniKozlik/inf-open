#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#define int ll

using namespace std;
using ll = long long;
using ld = long double;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<ld> r;
    vector<ld> l;
    set<ld> ind;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        r.push_back(a[i].second);
        ind.insert(a[i].first);
        ind.insert(a[i].second);
        ind.insert(a[i].first - 0.1);
        ind.insert(a[i].second - 0.1);
        ind.insert(a[i].first + 0.1);
        ind.insert(a[i].second + 0.1);
        l.push_back(a[i].first);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    vector<pair<int, int>> t;
    map<int, int> m;
    for (auto u : ind) {
        int cl = lower_bound(r.begin(), r.end(), u) - r.begin();
        int cr = n - (upper_bound(l.begin(), l.end(), u) - l.begin());
        m[n - cl - cr] = max(m[n - cl - cr], min(cl, cr) * 2);
    }
    for (auto u : m) {
        t.push_back({u.first, u.second});
    }
    sort(t.rbegin(), t.rend());
    vector<int> ans(q);
    vector<pair<int, int>> qu(q);
    int k;
    for (int i = 0; i < q; i++) {
        cin >> qu[i].first;
        qu[i].second = i;
    }
    sort(qu.begin(), qu.end());
    int j = 0;
    for (int i = 0; i < q; i++) {
        while ((qu[i].first - t[j].first) > t[j].second) {
            j++;
        }
        ans[qu[i].second] = max((qu[i].first - t[j].first + 1) / 2, 0ll);
    }
    for (auto u : ans) {
        cout << u << " ";
    }
    return 0;
}