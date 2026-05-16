#include <iostream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <random>
#include <numeric>


using namespace std;
using ll = long long;
using ld = long double;
using ui = unsigned int;
using ull = unsigned long long;

struct Seg {
    int l, r;

    bool operator<(const Seg a) const {
        return l < a.l;
    }
};

struct Event {
    int t, type, id;

    bool operator<(const Event a) const {
        if (t != a.t) return t < a.t;
        if (type != a.type) return type < a.type;
        return id < a.id;
    }
};

istream& operator>>(istream& is, Seg &a) {
    is >> a.l >> a.r;
    return is;
}

int count(vector<Event> evs) {
    int cur = 0;
    int ans = 0;
    for (auto [t, type, id] : evs) {
        if (type == 0) {
            cur++;
        } else {
            cur--;
        }
        ans = max(ans, cur);
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<Seg> segs(n);
    for (auto &i : segs) cin >> i;
    sort(segs.begin(), segs.end());
    vector<int> ans(q);
    vector<Event> evs;
    for (int i = 0; i < n; ++i) {
        evs.emplace_back(segs[i].l, 0, i);
        evs.emplace_back(segs[i].r, 1, i);
    }
    sort(evs.begin(), evs.end());
    vector<int> dp(n + 1);
    int cur = count(evs);
    for (int k = 1; k <= n; ++k) {
        dp[k] = dp[k - 1];
        if (k <= cur) {
            continue;
        }
        auto [l1, r1] = segs[0];
        auto [l2, r2] = segs.back();
        segs[0] = {l1, r2};
        segs[1] = {min(r1, l2), max(r1, l2)};
        sort(segs.begin(), segs.end());
        evs.clear();
        for (int i = 0; i < n; ++i) {
            evs.emplace_back(segs[i].l, 0, i);
            evs.emplace_back(segs[i].r, 1, i);
        }
        sort(evs.begin(), evs.end());
        cur = count(evs);
        dp[k]++;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << dp[k] << ' ';
    }
}