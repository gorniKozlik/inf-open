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


void build(int v, int l, int r, vector<int> &a) {
    if (r - l == 1) {
        t[v] = { a[l] };
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m, a);
    build(2 * v + 2, m, r, a);
    t[v].resize(t[2 * v + 1].size() + t[2 * v + 2].size());
    merge(all(t[2 * v + 1]), all(t[2 * v + 2]), t[v].begin());
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) {
        return r - l - (upper_bound(all(t[v]), x) - t[v].begin());
    }
    int m = (l + r) / 2;
    return get(2 * v + 1, l, m, ql, qr, x) + get(2 * v + 2, m, r, ql, qr, x);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> segl(n), segr(n);
    vector<int> kol;
    vector<int> v;
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
    for (int i = 0; i < n; ++i) {
        v.push_back(segl[i].second);
    }
    t.resize(4 * n);
    build(0, 0, n, v);
    int ans = inf;
    for (int i = 0; i < n; ++i) {
        int l = segl[i].first;
        int r = segl[i].second;
        int sz = 1 + get(0, 0, n, 0, i, l);
        int left = lower_bound(all(segr), pii{ l, -1 }) - segr.begin(), right = n - sz - left;
        int res = min(left, right) + n - sz - 2 * min(left, right);
        ans = min(ans, res);
    }
    int k;
    cin >> k;
    cout << ans << '\n';
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
