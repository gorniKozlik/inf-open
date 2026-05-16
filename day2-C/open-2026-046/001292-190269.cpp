#include <bits/stdc++.h>
#define int ll

using namespace std;
using ll = long long;
using ld = double;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ld> r(n);
    vector<ld> l(n);
    vector<ld> ind(n * 4);
    int sz = 0;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];

        ind[sz++] = (l[i]);
        ind[sz++] = (r[i]);
        ind[sz++] = (l[i] - 0.1);
        ind[sz++] = (r[i] - 0.1);
        ind[sz++] = (l[i] + 0.1);
        ind[sz++] = (r[i] + 0.1);
    }
    sort(ind.begin(), ind.end());
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