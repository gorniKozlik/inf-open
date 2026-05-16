// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> events;
    for (int i = 0; i < n; ++i) {
        int L, R;
        cin >> L >> R;
        events.emplace_back(L, 0);
        events.emplace_back(R, 1);
    }
    sort(events.begin(), events.end());
    int cur = 0, was = 0;
    vector <pair <int, int>> maybe;
    int mx = 0;
    for (const auto & [x, type] : events) {
        if (type == 0) {
            cur++;
            // cout << x << ": ";
            maybe.emplace_back(min(was, n - was - cur), cur);
            // cout << maybe.back().first << " " << cur << "\n";
            mx = max(cur, mx);
        } else {
            cur--;
            was++;
        }
    }
    while (q--) {
        int cnt;
        cin >> cnt;
        if (cnt <= mx) {
            cout << "0\n";
        } else {
            int ans = n + 8;
            for (const auto & [e, cur] : maybe) {
                if (cnt - cur <= 2 * e) {
                    ans = min(ans, (cnt - cur + 1) / 2);
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}