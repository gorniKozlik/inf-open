#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<algorithm>
#include<set>
#include<iomanip>
#include<random>
#include<chrono> 
using namespace std;
using ll = long long;
using ld = long double;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")

// #define int long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int mod = 998244353, inf = 1e9 + 1;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> segl(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        segl[i] = { l, r };
    }
    sort(all(segl));
    for (int i = 1; i < n; ++i) {
        if (segl[i].first <= segl[i - 1].second) {
            exit(1);
        }
    }
    cout << -1 << '\n';
}

signed main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
