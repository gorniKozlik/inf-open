
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
    ll cur = 0;
    sort(a.begin(), a.end());
    pll pr{-1e18, -1e18};
    ll sum = 0;
    vll b;
    for (ll i = 0; i < n; ++i) {
        if (pr.second >= a[i].first) {
            ++sum;
            pr = {a[i].first, min(pr.second, a[i].second)};
        } else {
            if (sum)
            b.push_back(sum);
            sum = 1;
            pr = a[i];
        }
    }
    if (sum) b.push_back(sum);
    vll res(n + 1, 1e18);
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
    //freopen("in.txt", "r", stdin);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
