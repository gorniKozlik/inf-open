#pragma gcc optimize("Ofast")
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <random>
#include <bitset>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;
#define int long long
using ll = long long;
using ld = long double;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...)
#endif
const int INF = 1e18;

int val(pair<int, int> a) {
    return a.first + a.second * 2;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    return val(a) < val(b);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> events;
    vector<int> ls, rs;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        r++;
        ls.emplace_back(l);
        rs.emplace_back(r - 1);
        events.emplace_back(l, 1);
        events.emplace_back(r, -1);
    }
    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    sort(events.begin(), events.end());
    dbg(ls);
    dbg(rs);
    int cnt = 0;
    vector<pair<int, int>> ops;
    for (int iter = 0; iter < events.size(); iter++) {
        auto [pos, type] = events[iter];
        cnt += type;
        if (iter + 1 != events.size() && events[iter + 1].first == pos) continue;
        int cntl = lower_bound(rs.begin(), rs.end(), pos) - rs.begin();
        int cntr = (ll) ls.size() - (upper_bound(ls.begin(), ls.end(), pos) - ls.begin());
        int can = min(cntl, cntr);
        if (abs(cntl - cntr) >= 1 && cnt > 0) {
            ops.emplace_back(cnt - 1, can + 1);
        }
        dbg(pos, cnt, can);
        dbg(cntl, cntr);
        ops.emplace_back(cnt, can);
    }
    sort(ops.begin(), ops.end(), comp);
    int sz = ops.size();
    vector<int> suf(sz);
    suf[sz - 1] = ops[sz - 1].first;
    for (int i = sz - 2; i >= 0; i--) {
        suf[i] = max(suf[i + 1], ops[i].first);
    }
    vector<int> help(sz);
    for (int i = 0; i < sz; i++) {
        help[i] = val(ops[i]);
    }
    dbg(help);
    dbg(suf);
    dbg(ops);
    for (int iter = 0; iter < q; iter++) {
        int x;
        cin >> x;
        int ind = lower_bound(help.begin(), help.end(), x) - help.begin();
        cout << (max(0ll, x - suf[ind]) + 1) / 2 << ' ';
    }
}
