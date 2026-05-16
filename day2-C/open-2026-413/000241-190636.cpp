#include <bits/stdc++.h>

#define int long long

using namespace std;

constexpr int N = 2e5 + 10;

void solve() {
    int n, q;
    cin >> n >> q;
    pair<int, int> a[n];
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    sort(a, a + n);
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << x / 2 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int dota = 1;
    //cin >> dota;
    while (dota--) {
        solve();
        cout << '\n';
    }
    return 0;
}
