
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;

void solve() {
    ll n, q;
    cin >> n >> q;
    vpll a(n);
    for (auto& [l, r] : a) cin >> l >> r;
    ll ans = 0;
    vll res(n + 1, 1e18);
    ll cur = 0;
    sort(a.begin(), a.end());
    set<pll> b(a.begin(), a.end());
    while (ans != n) {
        sort(a.begin(), a.end());
        vpll event;
        for (ll i = 0; i < n; ++i) {
            event.push_back({a[i].first, 1});
            event.push_back({a[i].second + 1, -1});
        }
        sort(event.begin(), event.end());
        ll cnt = 0;
        ll pre = 0;
        ll x0 = 0, val = 0, type = 0;
        ll x1 = 0;
        ll flag = 0;
        for (auto [x, t] : event) {
            cnt += t;
            if (flag) {
                x1 = x - 1;
            }
            flag = 0;
            if (cnt >= ans) {
                if (cnt > ans) {
                    x0 = 0;
                    val = 0;
                    type = 0;
                }
                if (pre && val <= 1) {
                    x0 = x;
                    val = 1;
                    type = 1;
                flag = 1;
                }
                if (pre && pre + cnt != n) {
                    x0 = x;
                    val = 2;
                    type = 0;
                }
                if (pre + cnt != n && val <= 1) {
                    x0 = x;
                    val = 1;
                    type = 2;
                flag = 1;
                }
                ans = cnt;
            }
            if (t == -1) ++pre;
        }
        for (ll i = 0; i <= ans; ++i) {
            res[i] = min(res[i], cur);
        }
        if (val == 2) {
            ll i0 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (r < x0) {
                    i0 = i;
                    break;
                }
            }
            if (i0 == -1) {
                while (1) {}
            }
            ll i1 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (l > x1) {
                    i1 = i;
                    break;
                }
            }
            if (i1 == -1) {
                while (1) {}
            }
            auto [l1, r1] = a[i0];
            auto [l2, r2] = a[i1];
            a[i0] = {l1, l2};
            a[i1] = {r1, r2};
        }
        else if (type == 1) {
            ll i0 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (r < x0) {
                    i0 = i;
                    break;
                }
            }
            if (i0 == -1) {
                while (1) {}
            }
            ll i1 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (l >= x0) {
                    i1 = i;
                    break;
                }
            }
            if (i1 == -1) {
                while (1) {}
            }
            auto [l1, r1] = a[i0];
            auto [l2, r2] = a[i1];
            a[i0] = {l1, l2};
            a[i1] = {r1, r2};
        }
        else if (type == 2) {
            ll i1 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (l > x1) {
                    i1 = i;
                    break;
                }
            }
            if (i1 == -1) {
                while (1) {}
            }
            ll i0 = -1;
            for (ll i = 0; i < n; ++i) {
                auto [l, r] = a[i];
                if (r <= x1) {
                    i0 = i;
                    break;
                }
            }
            if (i0 == -1) {
                while (1) {}
            }
            auto [l1, r1] = a[i0];
            auto [l2, r2] = a[i1];
            a[i0] = {l1, l2};
            a[i1] = {r1, r2};
        }
        ++cur;
    }
    for (ll i = 0; i < q; ++i) {
        ll cnt;
        cin >> cnt;
        cout << res[cnt] << '\n';
    }
}

int main() {
  //  freopen("in.txt", "r", stdin);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
