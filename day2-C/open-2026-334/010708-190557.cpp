//#pragma GCC optimize("Ofast, unroll-loops")

#include <bits/stdc++.h>
//#include<iostream>


using namespace std;
using ll = long long;
using sll = __int128_t;
int n, q;

void solve() {
    cin >> n >> q;
    vector<int> lt(n), rt(n);
    vector<pair<int, int> > points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        lt[i] = x;
        rt[i] = y;
        points.emplace_back(x, -1);
        points.emplace_back(y, 1);
    }
    sort(points.begin(), points.end());
    int cnt = 0;
    int cx = 2e9;
    int opened = 0, closed = 0;
    vector<int> ans(n + 1, 0);
    for (auto [x, st]: points) {
        cnt++;
        if (st == -1) {
            opened++;
        }
        if (cnt == n) {
            cx = x;
            break;
        }
        if (st == 1) {
            closed++;
        }
    }
    for (int i = 0; i <= n; i+=2) {
        ans[i] = i / 2;
        ans[i + 1] = i / 2;
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        if (q == 1 && k == n) {
            cout << n - opened << '\n';
            return;
        }
        cout << ans[k] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //cin >> t;
#endif
    while (t--) {
        solve();
    }
    return 0;
}
