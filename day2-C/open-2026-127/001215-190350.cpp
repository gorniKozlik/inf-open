#include <bits/stdc++.h>

#define int long long

using ll = long long;
using ld = long double;
using namespace std;
mt19937 rnd(239);

signed main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;
    vector <pair <int, int>> otr(n);
    vector <int> l(n), r(n), x;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        otr[i] = { l[i], r[i] };
        x.push_back(l[i]);
        x.push_back(r[i]);
    }
    sort(x.begin(), x.end());
    for (auto &i : l) i = lower_bound(x.begin(), x.end(), i) - x.begin();
    for (auto &i : r) i = lower_bound(x.begin(), x.end(), i) - x.begin();
    for (auto &i : otr) {
        i.first = lower_bound(x.begin(), x.end(), i.first) - x.begin();
        i.second = lower_bound(x.begin(), x.end(), i.second) - x.begin();
    }
    //for (auto i : otr) cout << i.first << " " << i.second << "\n";
    //return 0;
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    vector <int> lef(2 * n), mid(2 * n), rig(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        lef[i] = lower_bound(r.begin(), r.end(), i) - r.begin();
        rig[i] = n - (upper_bound(l.begin(), l.end(), i) - l.begin());
        mid[i] = n - lef[i] - rig[i];
    }
    //for (auto i : mid) cout << i << " ";
    //cout << "\n";
    int c, m, cur, z;
    vector <int> otv(n + 1, (int)2e9);
    for (int i = 0; i < 2 * n; i++) {
        c = mid[i];
        m = min(lef[i], rig[i]);
        for (int k = 1; k <= c; k++) otv[k] = min(otv[k], (int)0);
        for (int k = c + 1; k <= c + 2 * m; k ++) otv[k] = min(otv[k], (k + 1 - c) / 2);
        cur = m;
        for (int k = c + 2 * m + 1; k <= n; k++) {
            cur++;
            otv[k] = min(otv[k], cur);
        }
    }
    while (q--) {
        cin >> z;
        cout << otv[z] << "\n";
    }
    return 0;
}
