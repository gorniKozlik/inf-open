#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimise("O3, unroll-loops")
#pragma GCC target("avx,avx2,popcnt")

#define int long long
#define pb push_back
#define all(a) a.begin(), a.end()
#define db long double
#define ff first
#define ss second
#define vi vector<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvi vector<vi>

const int N = 5e5;
const int K = 20;
const int INF = 1e9;
const int mod = 998244353;
constexpr char nl = '\n';

// whos doper than this b1tch?


int bin_pow(int a, int p) {
    if (p < 0) {
        return 0;
    }
    if (p == 0) {
        return 1;
    }
    int res = 1;
    int pw = a;
    while (p) {
        if (p & 1) {
            res = res * pw % mod;
        }
        pw = pw * pw % mod;
        p >>= 1;
    }
    res %= mod;
    return res;
}

int sparse[K][N];

void build(vi a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = a[i];
    }
    for (int k = 1; k < K; ++k) {
        for (int i = 0; i + (1 << k) <= n; ++i) {
            sparse[k][i] = max(sparse[k - 1][i], sparse[k - 1][i + (1 << (k - 1))]);
        }
    }
}

int get(int l, int r) {
    int k = __lg(r - l);
    return max(sparse[k][l], sparse[k][r - (1 << k)]);
}

void solve() {
    int n, q;
    cin >> n >> q;
    set<pii > left, right;
    vi l(n), r(n);
    vi val;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        val.pb(l[i]);
        val.pb(r[i]);
    }
    sort(all(val));
    unordered_map<int, int> mp;
    int curr = 0;
    for (auto e: val) {
        mp[e] = curr++;
    }
    for (int i = 0; i < n; ++i) {
        l[i] = mp[l[i]];
        r[i] = mp[r[i]];
        left.insert({l[i], i});
        right.insert({r[i], i});
    }
    vi k(n);
    int mx = 0;
    vi queries(n + 1, INF);
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
        mx = max(mx, k[i]);
    }
    int t = 0;
    queries[1] = 0;
    int c = 0;
    while (c < n) {
        t++;
        c += 2;
        if (c < n) {
            queries[c + 1] = t;
        } else if (c == n) {
            queries[c] = t;
        }
    }
    for (int i = n - 1; i > 0; --i) {
        queries[i] = min(queries[i + 1], queries[i]);
    }
    for (auto e: k) {
        cout << queries[e] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
