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
    ll open = 0;
    ll close = 0;
    vector<ll> ans(n + 1, 1e10);
    ll ma = 0;
    for (ll i = 0; i < 2 * n; i++) {
        if (iv[i].type == 1) {
            open++;
            ll ost = n - open - close;
            ll have = open + min(close, ost) * 2;
            ma = max(ma, open);
            for (ll j = have; j >= open + 1; j--) {
                ll d = j - open + 1;
                if (ans[j] < d / 2) {
                    break;
                }
                ans[j] = min(ans[j], d / 2);
            }
            if (close > ost) {
                ll d = have - open + 2;
                ans[have + 1] = min(ans[have + 1], d / 2);
            }
        } else {
            ll ost = n - open - close;
            ll have = open + min(close, ost) * 2;
            ma = max(ma, open);
            for (ll j = have; j >= open + 1; j--) {
                ll d = j - open + 1;
                if (ans[j] < d / 2) {
                    break;
                }
                ans[j] = min(ans[j], d / 2);
            }
            if (ost > close) {
                ll d = have - open + 2;
                ans[have + 1] = min(ans[have + 1], d / 2);
            }
            open--;
            close++;
        }
    }
    for (ll i = 0; i <= ma; i++) {
        ans[i] = 0;
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
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
