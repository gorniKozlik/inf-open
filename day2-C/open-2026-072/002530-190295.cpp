#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#ifndef LOCAL
#pragma GCC optimize("O3")
#endif

using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ff first
#define ss second
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ld = long double;

constexpr int MOD = (int)1e9 + 7;

struct mint {
    int x;
    mint() : x(0) {}
    mint(int y) {
        if (y >= MOD) y -= MOD;
        if (y < 0) y += MOD;
        x = y;
    }
    mint(ll y) {
        if (y >= MOD) y %= MOD;
        if (y < 0) y += MOD;
        x = y;
    }
    mint operator+(const mint& b) const {
        return x + b.x;
    }
    mint operator-(const mint& b) const {
        return x - b.x;
    }
    mint operator*(const mint& b) const {
        return x * (ll) b.x;
    }
    mint& operator+=(const mint& b) {
        return *this = *this + b;
    }
    mint& operator-=(const mint& b) {
        return *this = *this - b;
    }
    mint& operator*=(const mint& b) {
        return *this = *this * b;
    }
};

struct point {
    ll x, y;

    point operator+(const point& b) const {
        return {x + b.x, y + b.y};
    }
    point operator-(const point& b) const {
        return {x - b.x, y - b.y};
    }
    ll operator*(const point& b) const {
        return x * b.x + y * b.y;
    }
    ll operator%(const point& b) const {
        return x * b.y - y * b.x;
    }
    ll len_sqr() const {
        return x * x + y * y;
    }
    ld len() const {
        return sqrtl(len_sqr());
    }
};

signed main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pii> ropes(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ropes[i] = {x, y};
    }
    vector<pii> f;
    sort(all(ropes));
    set<int> open;
    int full_left = 0;
    vector<int> ans(n + 1, 1e9);
    for (auto [x, y] : ropes) {
        open.insert(y);
        while (*open.begin() < x) {
            open.erase(open.begin());
            full_left++;
        }
        int w = open.size();
        int full_right = n - w - full_left;
        int q = min(full_left, full_right);
        // f.push_back({open.size(), open.size() + min(full_left, full_right)});
        for (int i = 1; i <= w; i++) {
            ans[i] = 0;
        }
        for (int i = 1; i <= q; i++) {
            ans[w + i * 2] = min(ans[w + i * 2], i);
            ans[w + i * 2 - 1] = min(ans[w + i * 2 - 1], i);
        }
        if (w + q * 2 < n)
            ans[w + q * 2 + 1] = min(ans[w + q * 2 + 1], q + 1);
    }
    while (q--) {
        int k;
        cin >> k;
        assert(ans[k] != 1e9);
        cout << ans[k] << ' ';
    }
}