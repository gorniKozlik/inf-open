#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

#define sz(a) ll((a).size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

mt19937 rnd(1245);

const ll mod = 1e9 + 7;
const int maxn = 5e5 + 1;
const int logn = 25;
const int inf = 2e9;
const ll INF = 2e18;
const ld eps = 1e-8;
const ld pi = acos(-1);


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > seg(n);
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].first >> seg[i].second;
    }
    vector<int> x(n + 1, inf);
    x[1] = 0;
    for (int i = 2; i < n + 1; ++i) {
        x[i] = i / 2;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << x[k] << '\n';
    }
}


signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
}
