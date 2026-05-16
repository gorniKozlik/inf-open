#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;

// #pragma GCC optimize("O3")
// #pragma GCC target("avx2")
// #pragma GCC optimize("unroll-loops")

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct ivent {
    ll x;
    ll type;
};

bool cmp(ivent& a, ivent& b) {
    if (a.x == b.x) {
        return a.type > b.type;
    }
    return a.x < b.x;
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ivent> iv(2 * n);
    for (ll i = 0; i < n; i++) {
        cin >> iv[2 * i].x >> iv[2 * i + 1].x;
        iv[2 * i].type = 1;
        iv[2 * i + 1].type = -1;
    }
    sort(iv.begin(), iv.end(), cmp);
    while (q--) {
        ll k;
        cin >> k;
        ll ans = 1e10;
        ll open = 0;
        ll close = 0;
        for (ll i = 0; i < 2 * n; i++) {
            if (iv[i].type == 1) {
                open++;
                ll ost = n - open - close;
                ll have = open + min(close, ost) * 2;
                if (k <= open) {
                    ans = 0;
                }
                if (k >= open + 1 && k <= have) {
                    ll d = k - open + 1;
                    ans = min(ans, d / 2);
                }
                if (close > ost && k == have + 1) {
                    ll d = have - open + 2;
                    ans = min(ans, d / 2);
                }
            } else {
                ll ost = n - open - close;
                ll have = open + min(close, ost) * 2;
                if (k <= open) {
                    ans = 0;
                }
                if (k >= open + 1 && k <= have) {
                    ll d = k - open + 1;
                    ans = min(ans, d / 2);
                }
                if (close < ost && k == have + 1) {
                    ll d = have - open + 2;
                    ans = min(ans, d / 2);
                }
                open--;
                close++;
            }
        }
        cout << ans << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
