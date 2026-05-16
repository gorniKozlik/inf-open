#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;


#define rep(x) for (int rep_i = 0; rep_i < x; rep_i++)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define int long long
const ll MOD = 998244353;
const ll LINF = 1ll << 61;
const int maxn = 100100;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



void solve() {
    int n, q;
    cin >> n >> q;
    rep(n) {
        int l, r;
        cin >> l >> r;
    }
    rep(q) {
        int x;
        cin >> x;
        cout << x / 2 << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(6);

    int mult = 1;
    //cin >> mult;
    while (mult--)
        solve();
    return 0;
}
