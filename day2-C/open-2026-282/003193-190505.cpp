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

vector<vector<int>> t;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> segl(n), segr(n);
    vector<int> kol;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        segl[i] = { l, r };
        segr[i] = { r, l };
        kol.push_back(l);
        kol.push_back(r);
    }
    sort(all(segl));
    sort(all(segr));
    vector<int> ans(n, inf);
    for (int i = 0; i < n; ++i) {
        int l = segl[i].first;
        int r = segl[i].second;
        if (pii{ r, l } != segr[i]) {
            exit(1);
        }
    }
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
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
