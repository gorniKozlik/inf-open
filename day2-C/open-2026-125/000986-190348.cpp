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

    while (q--) {
        int k;
        cin >> k;
        int ans = n / 2;
        int bal = 0;
        int cnt = 0;
        for (auto [x, e]: d) {
            bal += e;
//            cout << bal << ' ';
            {
                int mn = min(cnt, 2 * n - cnt - 2);
//                int mn = min(cnt, 2 * n - cnt - 1);
                if (bal + mn >= k) {
                    //cout << (k - bal + 1) / 2 << ' ';
                    ans = min(ans, (k - bal + 1) / 2);
                }
            }
            cnt++;
        }
        cout << max(ans, 0) << ' ';
    }

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