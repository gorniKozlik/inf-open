#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

//@formatter:off
template <typename T> istream& operator>>(istream& in, vector<T> &vec) { for (auto &i : vec) in >> i; return in; }
template <typename T> ostream& operator<<(ostream& out, vector<T> &vec) { for (auto &i : vec)  out << i << ' '; out << '\n'; return out; }
//@formatter:on

struct event {
    int x, e;
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<event> d;
    for (auto &[l, r]: a) {
        cin >> l >> r;
        d.emplace_back(l, 1);
        d.emplace_back(r, -1);
    }

    sort(d.begin(), d.end(), [](event a, event b) {
        if (a.x != b.x) return a.x < b.x;
        return a.e > b.e;
    });

    int bal = 0;
    int cnt = 0;
    vector<pair<int, int>> res;
    for (auto [x, e]: d) {
        bal += e;
        if (e < 0) cnt++;
        {
            int mn = min(cnt, n - cnt - bal);
            res.emplace_back(bal + 2 * mn, bal);
            if (bal + 2 * mn) {
                //cout << (k - bal + 1) / 2 << ' ';
                //ans = min(ans, (k - bal + 1) / 2);
            }
        }
    }
    sort(res.begin(), res.end());
    vector<pair<int,int>> que(q);
    for (int i = 0; i < q; ++i) {
        cin >> que[i].first;
        que[i].second = i;
    }

    sort(que.begin(), que.end());
    int l = res.size() - 1;
    int mx = 0;
    vector<int> ans(q);
    for (int i = q - 1; i >= 0; i--) {
        while (l >= 0 && res[l].first >= que[i].first) mx = max(mx, res[l].second), l--;
        ans[que[i].second] = (que[i].first - mx + 1) / 2;
    }
    cout << ans;
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}