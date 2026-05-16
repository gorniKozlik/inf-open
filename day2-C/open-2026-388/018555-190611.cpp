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
    set<pair<int, int>> s1, s2;
    for (int i = 0; i < n; ++i) {
        cin >> v[i].ff >> v[i].ss;
        s1.insert({v[i].ss, v[i].ff});
        s2.insert({v[i].ff, v[i].ss});
    }

    int k;
    cin >> k;

    int cnt = 0;
    sort(all(v));

    for (int i = 0; i < n - i - 1; ++i) {
        //int j = n - i - 1;
        auto x = *s1.begin(), y = *s2.rend();
        if (!peres(x, y)) ++cnt;
        s1.erase(s1.begin());
        s2.erase((--s2.end()));
        s1.erase({y.ss, y.ff});
        s2.erase({x.ss, x.ff});
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
