// #include </home/olymp/work/untitled1/debug.h>
// #define M(x) #x

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
using ll = long long;

# define len(x) ((ll) x.size())
const ll inf = 1e18;

void solve() {
    ll n, q;
    cin >> n >> q;

    vector<pair<ll, ll>> a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }

    vector<ll> ans(n + 1, inf);
    map<ll, pair<ll, ll>> cnt;
    for (ll i = 0; i < n; ++i) {
        cnt[a[i].first].first++;
        cnt[a[i].second].second++;
    }

    vector<ll> zeros(n + 1, inf), arith(n + 1, inf), odd(n + 1, inf), even(n + 1, inf);

    ll cnt_closed = 0;
    ll cnt_open = 0;
    for (auto& [x, y] : cnt) {
        ll balance = y.first + cnt_open - cnt_closed;
        ll left = cnt_closed;
        ll right = n - cnt_open - y.first;
        ll maxi = min(left, right) * 2 + balance;
        ll add = 0;
        if (left < right) {
            add += min(y.second, right - left);
        }
        if (left > right) {
            add += min(y.first, left - right);
        }
        zeros[balance] = 0;
        if ((balance + 1) % 2 == 0) {
            even[balance + 1] = 1;
        } else {
            odd[balance + 1] = 1;
        }
        ll val = (maxi - balance - 1) / 2 + 1;
        arith[maxi + 1] = 1 + val;
        cnt_open += y.first;
        cnt_closed += y.second;
    }
    ll mn = inf;
    for (ll i = n; i >= 0; --i) {
        mn = min(mn, zeros[i]);
        ans[i] = min(ans[i], mn);
    }
    mn = inf;
    for (ll i = 0; i <= n; ++i) {
        mn += 1;
        mn = min(mn, arith[i]);
        ans[i] = min(ans[i], mn);
    }

    mn = inf;
    for (ll i = 0; i <= n; ++i) {
        if (i % 2 == 0) {
            mn += 1;
            mn = min(mn, even[i]);
        }
        ans[i] = min(ans[i], mn);
    }

    mn = inf;
    for (ll i = 0; i <= n; ++i) {
        if (i % 2 == 1) {
            mn += 1;
            mn = min(mn, odd[i]);
        }
        ans[i] = min(ans[i], mn);
    }

    ll k;
    while (q--) {
        cin >> k;
        cout << ans[k] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}