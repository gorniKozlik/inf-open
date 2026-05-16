#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) solve();
}

#define int ll

int mod = 998244353, inf = 1e9+100;
ll infll = 1e18+100;

struct Event {
    int x;
    int t;

    Event() {}
    Event(int x, int t) : x(x), t(t) {}

    bool operator<(const Event& rhs) const {
        return x < rhs.x || (x == rhs.x && t < rhs.t);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> LR, RL;
    set<Event> e;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        LR[l] = r;
        RL[r] = l;
        e.emplace(l, -1);
        e.emplace(r, 1);
    }
    vector<int> ans(n + 1, infll);
    auto find_bal = [&] () {
        int bal = 0;
        int res = 0;
        for (auto [x, t] : e) {
            res = max(res, bal);
            bal -= t;
            res = max(res, bal);
        }
        return res;
    };
    int first = find_bal();
    fill(ans.begin(), ans.begin() + first + 1, 0);
    auto intersect = [&] (int l, int r, int x, int y) {
        if (l >= y || r <= x) return false;
        return true;
    };
    int cnt = 0;
    while (LR.size() > 1) {
        auto [l1, r1] = *LR.begin();
        auto [r2, l2] = *RL.rbegin();
        LR.erase(RL.rbegin()->second);
        RL.erase(--RL.end());
        if (intersect(l1, r1, l2, r1)) continue;
        RL.erase(LR.begin()->second);
        LR.erase(LR.begin());
        e.erase({l1, -1});
        e.erase({r1, 1});
        e.erase({l2, -1});
        e.erase({r2, 1});
        e.emplace(l1, -1);
        e.emplace(l2, 1);
        e.emplace(r1, -1);
        e.emplace(r2, 1);
        int k = find_bal();
        ans[k] = min(ans[k], ++cnt);
        ans[k - 1] = min(ans[k - 1], ans[k]);
    }
    for (int i = n - 2; i >= 0; --i) ans[i] = min(ans[i], ans[i + 1]);
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << '\n';
    }
}