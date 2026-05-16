// dimaloh

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using lll = __int128;
using pii = pair<int, int>;
using ld = long double;
using pll = pair<ll, ll>;

#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()


template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18;
const int inf = 1e9, mod = 1e9 + 7, sz = 5e5 + 10, logn = 20;
const ld pi = acosl(-1), eps = 1e-8;

mt19937 rnd(87438);

void solve() {
    int n, q; cin >> n >> q;
    vector<pii>v(n);
    vector<int>p;
    unordered_map<int, int>mpl, mpr;
    for (auto &[l, r] : v) {
        cin >> l >> r;
        p.push_back(l);
        p.push_back(r);
        mpl[l]++;
        mpr[r]++;
    }
    sort(all(p));

    int a1 = 0, a2 = n;
    int curK = 0;
    vector<pii>v2;
    for (auto &x : p) {
        a2 -= mpl[x];
        int cur = n - a1 - a2;
        curK = max(curK, cur);

        int b1 = mpr[x], b2 = mpl[x];

        v2.emplace_back(cur + 2 * min(a1, a2), cur);
        if (a1 > a2 && b2) v2.back().first++;
        if (a1 < a2 && b1) v2.back().first++;
        // cout << x << ' ' << a1 << ' ' << a2 << ' ' << b1 << ' ' << b2 << endl;
        a1 += mpr[x];
    }
    sort(all(v2));
    vector<int>sf(2 * n);
    sf[2 * n - 1] = v2[2 * n - 1].second;
    for (int i = 2 * n - 2; i >= 0; --i) {
        sf[i] = max(sf[i + 1], v2[i].second);
    }
    while (q--) {
        int k; cin >> k;
        if (k <= curK) {
            cout << "0 ";
            continue;
        }
        int ind = lower_bound(all(v2), make_pair(k, 0)) - v2.begin();
        cout << (k - sf[ind] + 1) / 2 << ' ';
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(20);

    int t = 1;

#ifdef DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> t;
#endif


    while (t--) {
        solve();
        cout << '\n';
    }
}