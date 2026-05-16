
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve();

signed main() {
    solve();
}

struct zxc {
    ll x;
    ll fl;
};

bool cmp(zxc a, zxc b) {
    return a.x < b.x || (a.x == b.x && a.fl > b.fl);
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<zxc> v;
    vector<ll>ls(n), rs(n);
    for (ll i = 0; i < n; i++) {
        cin >> ls[i] >> rs[i];
        v.emplace_back(ls[i], 1);
        v.emplace_back(rs[i], -1);
    }
    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    sort(v.begin(), v.end(), cmp);
    ll mx = 1e9, cnt = 0;
    vector<ll>ans(n + 1, 1e9);
    for (ll i = 0; i < 2 * n; i++) {
        ll l1 = -1, r1 = n, l2 = -1, r2 = n;
        while (r1 - l1 > 1) {
            ll m = (r1 + l1) / 2;
            if (rs[m] >= v[i].x) r1 = m;
            else l1 = m;
        }
        while (r2 - l2 > 1) {
            ll m = (r2 + l2) / 2;
            if (ls[m] > v[i].x) r2 = m;
            else l2 = m;
        }
        ans[min(r1, n - r2) * 2 + cnt] = min(ans[min(r1, n - r2) * 2 + cnt], min(r1, n - r2));
        cnt += v[i].fl;
    }
    ll u = 0;
    set<ll> deq;
    for (ll i = n; i > -1; i--) {
        while (!deq.empty() && *deq.begin() - u < 0) {
            deq.erase(deq.begin());
        }
        if (!deq.empty() && *deq.begin() - u < ans[i]) {
            ans[i] = *deq.begin() - u;
        }
        deq.emplace(ans[i] + u);
        u = (n - i + 1 +  (n % 2)) / 2;
    }
    ll p = 0, mn = 1e9;
    for (ll i = 0;i <= n; i++) {
        if (mn + i - p > ans[i]) {
            mn = ans[i];
            p = i;
        }
        ans[i] = mn + i - p;
    }

    while (q--) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
