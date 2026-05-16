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

    vector<ll> zeros(n + 1, inf);
    vector<vector<ll>> open_arith(n + 1), close_arith(n + 1);
    vector<vector<ll>> open_odd(n + 1), close_odd(n + 1);
    vector<vector<ll>> open_even(n + 1), close_even(n + 1);

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
        for (ll i = balance + 1; i <= maxi; ++i) {
            ans[i] = min(ans[i], (i - balance - 1) / 2 + 1);
        }
        ll val = (maxi - balance - 1) / 2 + 1;
        for (ll i = maxi + 1; i <= maxi + add; ++i) {
            ans[i] = min(ans[i], val + (i - maxi));
        }
        cnt_open += y.first;
        cnt_closed += y.second;
    }
    ll mn = inf;
    for (ll i = n; i >= 0; --i) {
        mn = min(mn, zeros[i]);
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