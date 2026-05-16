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
            maybe.emplace_back(2*min(was, (n - was - cur) + 1), cur - 1);
            maybe.emplace_back(2*min(was, (n - was - cur)), cur);
            mx = max(cur, mx);
        } else {
            maybe.emplace_back(2*min(was + 1, (n - was - cur)), cur - 1);
            maybe.emplace_back(2*min(was, (n - was - cur)), cur);
            cur--;
            was++;
        }
    }
    sort(maybe.begin(), maybe.end(), [&](const pair <int, int> & a, const pair <int, int> & b) {
        return (a.first + a.second > b.first + b.second);
    });
    int k = maybe.size();
    vector <int> mini(k + 1, n + 8);
    for (int i = 0; i < k; ++i) {
        mini[i + 1] = min(mini[i], maybe[i].second);
    }
    while (q--) {
        int cnt;
        cin >> cnt;
        if (cnt <= mx) {
            cout << "0\n";
        } else {
            int L = 0, R = k + 1;
            while (R - L > 1) {
                int mid = (L + R) >> 1;
                if (maybe[mid].first + maybe[mid].second >= cnt) {
                    L = mid;
                } else {
                    R = mid;
                }
            }
            cout << (cnt + 1 - mini[L]) / 2 << "\n";
        }
    }
    return 0;
}