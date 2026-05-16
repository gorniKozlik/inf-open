#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using cll = const long long;
using ull = unsigned long long;

void Kus() { exit(0); }
ll rnd(cll RMOD) { return (rand() * rand()) % RMOD; };

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename a>
using pbds_tree = __gnu_pbds::tree<a, __gnu_pbds::null_type, less/**_equal*/<a>, 
__gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template<typename a>
struct oset : public pbds_tree<a> {
    auto operator [] (ll index) {
        return *this -> find_by_order(index);
    }
};

#define INTERACTIVE false

/** fun begins */

cll MOD = 998244353;

// ll fen[1000000];

// ll fen_sum(ll idx) {
//     ll sum = 0;
//     for (ll i = idx; i > 0; i -= i & -i) {
//         sum += fen[i];
//     }
//     return sum;
// }

// void fen_upd(ll idx, ll x) {
//     for (ll i = idx; i <= n; i += i & -i) {
//         fen[i] += x;
//     }
// }

// ll fen_get(ll tl, ll tr) {
//     return fen_sum(tr) - fen_sum(tl - 1);
// }

ll bpow(ll x, ll y) {
    vector <ll> p(60, 1);
    p[1] = x;
    for (ll i = 2; i < 60; i++) {
        p[i] = (p[i - 1] * p[i - 1]) % MOD;
    }
    ll res = 1;
    for (ll i = 33; i >= 0; i--) {
        if (y >= (1 << i)) {
            res = (res * p[i + 1]) % MOD;
            y -= (1 << i);
        }
    }
    return res;
}

void rawr() {
    ll n, q;
    cin >> n >> q;
    vector <ll> l, r;
    vector <pair <ll, ll> > v;
    for (ll i = 0; i < n; i++) {
        ll tl, tr;
        cin >> tl >> tr;
        l.push_back(tl);
        r.push_back(tr);
        v.push_back({tl, -1});
        v.push_back({tr, 1});
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    sort(v.begin(), v.end());
    ll cnt = 0, res = 0, tl = 0, tr = 0;
    bool flag = 0;
    vector <tuple <ll, ll, ll> > ans;
    for (ll i = 0; i < 2 * n; i++) {
        auto [x, z] = v[i];
        cnt -= z;
        if (z == -1) {
            tl = x;
            flag = 1;
        }
        if (z == 1 && flag == 1) {
            tr = x;
            flag = 0;
            ans.push_back({tl, tr, cnt});
        }
    }
    tl = 0;
    tr = 0;
    ll mn = -1e18, mx = 1e18;
    vector <ll> ams(n + 1, 1e18);
    for (ll zzz = 0; zzz < ans.size(); zzz++) {
        auto [l1, r1, xxx] = ans[zzz];
        while (tl < n && l[tl] <= r1) {
            tl++;
        }
        while (tr < n && r[tr] < l1) {
            tr++;
        }
        mx = min(mx, (abs(n - tl - tr)));
        for (ll i = 0; i <= n; i++) {
            ll k = i;
            mn = (n - xxx - mx) / 2;
            if (k <= xxx) {
                ams[i] = 0;
            } else if (k <= xxx + 2 * mn) {
                ams[i] = min(ams[i], (k - xxx + 1) / 2);
            }  else {
                ams[i] = min(ams[i], k - xxx - mn);
            }
        }
    }
    mn = (n - res - mx) / 2;
    while (q--) {
        ll k;
        cin >> k;
        cout << ams[k] << " ";
    }
}

/** fun is over */

int32_t main() {
    srand(time(0));
    random_device rd;
    mt19937 gen(rd());
#if defined (LOCAL) && (INTERACTIVE == false)
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    /** Meow begins */
    ll _ = 1;
    // cin >> _;
    while (_--) {
        rawr();
    }
    /** Meow is over */
    Kus();
}
