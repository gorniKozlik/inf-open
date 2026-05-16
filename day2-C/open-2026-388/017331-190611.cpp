#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ff first
#define ss second

bool peres(pair<int, int> x, pair<int, int> y) {
    if (x.ff > x.ss) swap(x.ff, x.ss);
    if (y.ff > y.ss) swap(y.ff, y.ss);

    if (x > y) swap(x, y);

    auto [l1, r1] = x;
    auto [l2, r2] = y;

    if (r1 < l2) return false;
    else return true;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].ff >> v[i].ss;
        v[i].ss = -v[i].ss;
    }

    int k;
    cin >> k;

    int cnt = 0;
    sort(all(v));

    for (int i = 0; i < n - i - 1; ++i) {
        int j = n - i - 1;
        v[i].ss = -v[i].ss;
        v[j].ss = -v[j].ss;
        if (!peres(v[i], v[j])) ++cnt;
    }

    cout << cnt << '\n';

    /*
    while (q--) {
        int k;
        cin >> k;

    }
    */
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
