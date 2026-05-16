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

// андрея глазырина надо забанить почему он так стремно лыбит на меня

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
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        left.insert({l[i], i});
        right.insert({r[i], i});
    }
    if (q != 1) return;
    int k;
    cin >> k;
    if (k != n) return;
    int t = 0;
    while (true) {
        auto lm = *left.rbegin();
        auto rm = *right.begin();
        if (lm.ff <= rm.ff) {
            cout << t;
            return;
        }
        left.erase(*left.rbegin());
        right.erase(right.begin());
        int i1 = lm.ss;
        int i2 = rm.ss;
        left.erase({r[i1], i1});
        right.erase({l[i2], i2});
        l[i2] = l[i2];
        r[i2] = r[i1];
        l[i1] = rm.ff;
        r[i1] = lm.ff;

        left.insert({l[i2], i2});
        right.insert({r[i2], i2});
        left.insert({l[i1], i1});
        right.insert({r[i1], i1});
        t++;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
