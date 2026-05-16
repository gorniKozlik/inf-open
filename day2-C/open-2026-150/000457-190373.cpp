#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <x86intrin.h>



#ifndef DEBUG
// #pragma GCC optimize("avx2")
// #pragma GCC optimize("O3")
#endif

using namespace __gnu_pbds;
using namespace std::ranges;

using ll = long long;
using ld = long double;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = std::pair<ll, ll>;

const ll MOD = 998244353;
const ll MOD1 = 1000000007;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    ll n, q;
    std::cin >> n >> q;
    std::vector<pll> evs;
    for (int i = 0; i < n; ++i) {
        ll l, r;
        std::cin >> l >> r;
        evs.push_back({l, -1});
        evs.push_back({r, 1});
    }
    sort(evs);
    ll cnt0 = 0, cnt1 = 0, cnt2 = n;
    std::vector<ll> anses(3 * n + 1);
    for (int i = 0; i < 2 * n; ++i) {
        if (evs[i].second == -1) {
            --cnt2;
            ++cnt1;
        }
        else {
            ++cnt0;
            --cnt1;
        }
        anses[cnt1 + 2 * std::min(cnt2, cnt0)] = std::max(anses[cnt1 + 2 * std::min(cnt2, cnt0)], cnt1);
    }
    for (int i = 3 * n - 1; i >= 0; --i) {
        anses[i] = std::max(anses[i], anses[i + 1]);
    }
    for (int i = 0; i < q; ++i) {
        ll k;
        std::cin >> k;
        std::cout << std::max(0ll, (k - anses[k] + 1) / 2) << ' ';
    }
}

int main() {
#ifdef DEBUG
    std::freopen("input.txt", "r", stdin);
#endif
    std::cin.tie(0)->std::ios::sync_with_stdio(0);
    int tt = 1;
    // std::cin >> tt;
    while (tt--) {
        solve();
    }
}
