#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>

#define all(a) a.begin(), a.end()

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Event {
    int x, d;

    bool operator<(Event const &e) const {
        return x < e.x;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> z(n);
    vector<int> x(n + n);
    for (int i = 0; i < n; ++i) {
        cin >> z[i].first >> z[i].second;
        x[i + i] = z[i].first;
        x[i + i + 1] = z[i].second;
    }
    sort(all(x));
    for (int i = 0; i < n; ++i) {
        z[i].first = lower_bound(all(x), z[i].first) - x.begin();
        z[i].second = lower_bound(all(x), z[i].second) - x.begin();
    }
    vector<Event> events(n + n);
    for (int i = 0; i < n; ++i) {
        events[i + i] = {z[i].first, 1};
        events[i + i + 1] = {z[i].second, -1};
    }
    sort(all(events));
    vector<pair<int, pii>> centers(n + n);
    int c = 0, f = 0;
    for (int i = 0; i < n + n; ++i) {
        if (events[i].d == -1) {
            f++;
        }
        c += events[i].d;

        centers[i] = {c, {f, n - c - f}};
    }
    vector<int> ans(n + 1, 1e9);
    for (int i = 0; i < n + n; ++i) {
        for (int j = centers[i].first; j >= 0 and ans[j] == 1e9; --j) {
            ans[j] = 0;
        }
    }

    set<pii> a;
    multiset<int> m;
    multiset<int> b;
    for (int i = 0; i < centers.size(); ++i) {
        a.emplace(centers[i].first + 2 * min(centers[i].second.first, centers[i].second.second), i);
        m.insert(-centers[i].first);
    }

    for (int i = 0; i <= n; ++i) {
        while (!a.empty() and a.begin()->first <= i) {
            b.insert(-centers[a.begin()->second].first - min(centers[a.begin()->second].second.first, centers[a.begin()->second].second.second));
            m.extract(-centers[a.begin()->second].first);
            a.erase(a.begin());
        }
        if (!m.empty()) {
            ans[i] = min(ans[i], max((i + *m.begin() + 1) / 2, 0));
        }
        if (!b.empty()) {
            ans[i] = min(ans[i], max(0, i + *b.begin()));
        }
    }

    while (q--) {
        int v;
        cin >> v;
        cout << ans[v] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}