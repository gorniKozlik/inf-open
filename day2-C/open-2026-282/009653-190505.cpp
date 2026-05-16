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
    vector<int> ans(n, inf);
    vector<tuple<int, int, int>> ass;
    int mx = 0;
    int id = 0;
    int mx1 = 0, id1 = 0;
    for (int i = 0; i < n; ++i) {
        int l = segl[i].first;
        int r = segl[i].second;
        int sz = 1 + get(0, 0, n, 0, i, l);
        if (sz > mx) {
            mx = sz, id = i;
        }
        int left = lower_bound(all(segr), pii{ l, -1 }) - segr.begin(), right = n - sz - left;
        ass.push_back({ sz, left, right });
        if (right - left == 1) {
            if (sz > mx1) {
                mx1 = sz;
                id1 = i;
            }
        }
        for (int j = 1; j <= sz; ++j) {
            ans[j - 1] = min(ans[j - 1], 0);
        }
        //auto f = [&](int x) {
        //    if (x <= sz) return 0;
        //    if (x <= sz + min(left, right) * 2) return (x - sz + 1) / 2;
        //    return min(left, right)
        //    };
        int last = 0;
        for (int j = sz + 1; j <= sz + min(left, right) * 2; ++j) {
            ans[j - 1] = min(ans[j - 1], (j - sz + 1) / 2);
            last = (j - sz) / 2;
        }
        for (int j = sz + min(left, right) * 2 + 1; j <= n; ++j) {
            ans[j - 1] = min(ans[j - 1], last + 1);
            last++;
        }
    }
    for (int i = 0; i < n; ++i) {
        auto[sz, left, right] = ass[i];
        if (i == id || i == id1) {
            for (int j = 1; j <= sz; ++j) {
                ans[j - 1] = min(ans[j - 1], 0);
            }
            //auto f = [&](int x) {
            //    if (x <= sz) return 0;
            //    if (x <= sz + min(left, right) * 2) return (x - sz + 1) / 2;
            //    return min(left, right)
            //    };
            int last = 0;
            for (int j = sz + 1; j <= sz + min(left, right) * 2; ++j) {
                ans[j - 1] = min(ans[j - 1], (j - sz + 1) / 2);
                last = (j - sz) / 2;
            }
            for (int j = sz + min(left, right) * 2 + 1; j <= n; ++j) {
                ans[j - 1] = min(ans[j - 1], last + 1);
                last++;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << ans[k - 1] << ' ';
    }
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
