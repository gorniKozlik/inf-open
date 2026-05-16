#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

#ifndef ABOBA
#pragma GCC traget("avx2")
#pragma GCC optimize("O3")
#endif

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using uint = unsigned int;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr ll inf = 1e18, mod = 998244353;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll> > a(n);
    vector<ll> all;
    for (auto &[l, r]: a) {
        cin >> l >> r;
        all.emplace_back(l);
        all.emplace_back(r);
    }
    sort(all.begin(), all.end());
    vector<ll> ans(n);
    ll m = all[n];
    vector<ll> inds;
    for (ll i = 0; i < n; ++i) {
        if (a[i].first >= m) {
            inds.emplace_back(i);
            ++ans[n - 1];
        }
    }
    for (ll i = n - 3; i >= 0; i -= 2) {
        ans[i + 1] = ans[i + 2];
        ans[i] = ans[i + 2] - 1;
    }
    ans[0] = 0;
    while (q--) {
        ll k;
        cin >> k;
        cout << ans[k - 1] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll tt = 1;
    //cin >> tt;
    while (tt--) solve();
    return 0;
}
