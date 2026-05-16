#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

void minik(int &a, int b) {
    a = min(a, b);
}

void getless(vector<pair<int, int>> &ot) {
    int n = ot.size();
    vector<pair<int, int>> bad = ot;
    set<int> is;
    for (int i = 0; i < n; ++i) {
        is.insert(bad[i].first);
        is.insert(bad[i].second);
    }
    unordered_map<int, int> less;
    int k = 0;
    for (auto t : is) {
        less[t] = k;
        k++;
    }
    for (int i = 0; i < n; ++i) {
        ot[i].first = less[bad[i].first];
        ot[i].second = less[bad[i].second];
    }
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ot(n);
    for (int i = 0; i < n; ++i) cin >> ot[i].first >> ot[i].second;
    getless(ot);
    vector<pair<int, int>> ev;
    for (auto [l, r] : ot) {
        ev.push_back({l, 0});
        ev.push_back({r, 1});
    }
    sort(ev.begin(), ev.end());
    // for (auto [l, r] : ev) cout << l << ' ' << r << endl;
    // cout << endl;
    vector<int> in(n * 2), l(n * 2), r(n * 2);
    int t = 0;
    int have = 0;
    for (auto [x, e] : ev) {
        l[x] = have;
        if (e == 0) t++;
        in[x] = t;
        if (e == 1) {
            have++;
            t--;
        }
    }
    reverse(ev.begin(), ev.end());
    t = 0;
    have = 0;
    for (auto [x, e] : ev) {
        r[x] = have;
        if (e == 0) have++;
    }
    // for (int i : in) cout << i << ' ';
    // cout << endl;
    // for (int i : l) cout << i << ' ';
    // cout << endl;
    // for (int i : r) cout << i << ' ';
    // cout << endl;
    vector<int> res(n + 1, inf);
    for (int i = 0; i < n * 2; ++i) {
        for (int ki = 0; ki <= in[i]; ++ki) res[ki] = 0;
        for (int ki = 1; ki <= min(l[i], r[i]) && in[i] + ki * 2 <= 10; ++ki) {
            minik(res[in[i] + ki * 2 - 1], ki);
            minik(res[in[i] + ki * 2], ki);
        }
        for (int ki = 1; ki <= abs(l[i] - r[i]) && in[i] + min(l[i], r[i]) * 2 + ki <= 10; ++ki)
            minik(res[in[i] + min(l[i], r[i]) * 2 + ki], min(l[i], r[i]) + ki);
    }
    for (int qi = 0; qi < q; ++qi)  {
        int t;
        cin >> t;
        cout << res[t] << ' ';
    }
}