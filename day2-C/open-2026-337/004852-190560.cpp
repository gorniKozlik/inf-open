
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
    ll m = 0;
    for (auto& [l, r] : a) cin >> l >> r;
    {
        set<ll> unique;
        for (ll i = 0; i < n; ++i) unique.insert(a[i].first), unique.insert(a[i].second);
        map<ll, ll> match;
        ll mex = 0;
        for (ll i : unique) match[i] = mex, ++mex;
        for (auto& [l, r] : a) {
            l = match[l];
            r = match[r];
            m = max(m, r + 1);
        }
    }
    ll cur = 0;
    sort(a.begin(), a.end());
    vll b;
    vll dp2(m + 1, 0);
    ll N = n;
    while (a.size() != 0) {
        vll dp(m);
        ll mx = 0;
        for (ll i = 0; i < n; ++i) {
            for (ll j = a[i].first; j <= a[i].second; ++j) {
                dp[j]++;
            }
        }
        for (ll i = 0; i < m; ++i) if (dp[i] > dp[mx]) mx = i;
        vpll a2;
        dp2[mx] = dp[mx];
        for (ll i = 0; i < n; ++i) {
            if (a[i].first <= mx && a[i].second >= mx) {

            } else {
                a2.push_back(a[i]);
            }
        }
        a = a2;
        n = a.size();
    }
    for (ll i = 0; i < m; ++i) if (dp2[i] != 0) b.push_back(dp2[i]);
    vll res(n + 1, 1e18);
    n= N;
    for (ll i = 0; i < b.size(); ++i) {
        vll b_copy = b;
        ll pr = i - 1;
        ll nxt = i + 1;
        vll cur_ans(n + 1, 1e18);
        ll pr_a = 0;
        ll x = 0;
        for (ll i = 0; i <= b[i]; ++i) cur_ans[i] = 0;
        pr_a = b[i];
        while (b[i] < n) {
            if (pr != -1) {
                b[pr] -= 1;
                if (b[pr] == 0) --pr;
                b[i] += 1;
            }
            if (nxt != b.size()) {
                b[nxt] -= 1;
                if (b[nxt] == 0) ++nxt;
                b[i] += 1;
            }
            ++x;
            for (ll j = pr_a + 1; j <= b[i]; ++j) cur_ans[j] = x;
            pr_a = b[i];
        }
        if (cur_ans < res) res = cur_ans;
        b = b_copy;
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
