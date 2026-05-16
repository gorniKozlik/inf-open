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
    for (auto &[l, r] : v) {
        cin >> l >> r;
        p.push_back(l);
        p.push_back(r);
    }
    sort(all(p));
    while (q--) {
        int k; cin >> k;
        int ans = n; 
        for (auto &x : p) {
            int cur = 0;
            for (auto &[l, r] : v) {
                if (l <= x && r >= x) {
                    cur++;
                }
            }
            if (cur == k) {
                ans = 0;
                break;
            }
            int a1 = 0, a2 = 0;
            int b1 = 0, b2 = 0;
            for (auto &[l, r] : v) {
                if (r < x) a1++;
                else if (l > x) a2++;
                else if (r == x) b1++;
                else if (l == x) b2++;
            }
            if (cur + 2 * min(a1, a2) >= k) {
                ans = min(ans, (k - cur + 1) / 2);
            } else {
                if (a1 == a2) {
                    continue;
                } if (a1 > a2 && b2) {
                    if (cur + 2 * a2 + 1 >= k) {
                        ans = min(ans, a2 + 1);
                    }
                } else if (a1 < a2 && b1) {
                    if (cur + 2 * a1 + 1 >= k) {
                        ans = min(ans, a1 + 1);
                    }
                }
            }
        }
        cout << ans << ' ';
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