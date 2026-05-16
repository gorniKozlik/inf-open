
#include <bits/stdc++.h>
#define int int64_t
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;




int32_t main() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> a;

    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        a.push_back({l, 1});
        a.push_back({r, 2});
    }

    sort(all(a));

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        if (a[i].second == 2)
            cnt++;
    }

    while (q--) {
        int x; cin >> x;
        cout << cnt;
    }
}