
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define db double
#define ll long long
#define pii pair<int, int>
#define tiii tuple<int ,int, int >
#define tiiii tuple<int, int, int, int>
#define tiiiii tuple<int, int, int, int, int>
#define ve vector
#define vi ve<int>
#define vvi ve<vi>
#define all(a) a.begin(), a.end()
#define allr(a) a.rbegin(), a.rend()
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)
#define cin(a) for(auto &now : a) cin >> now;
#define print(a, s) for(auto now : a) cout << now << s;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rnd(time(0));

void solve() {
    int n, q; cin >> n>> q;
    ve<tiii> line;
    vi l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        line.push_back({l[i], 1, i});
        line.push_back({r[i], -1, i});
    }
    sort(all(line));
    int tk = 0, cl = 0, mxtk = 0;
    ve<ve<pii>> l2(n + 1);
    int timer = -1;
    for (auto [x, t, ind] : line) {
        l2[tk].push_back({-1, ++timer});
        l2[tk + 2 * min(cl ,n - tk - cl)].push_back({1, timer});
        cl += (t == -1);
        tk += t; chmax(mxtk, tk);

    }
    set<pii> st0;
    sort(all(l2));
    ve<pii> vals(timer + 2);
    vi ans(n + 1, 1e18);
    for (int x = 0; x <= n; ++x){
        sort(all(l2[x]));
        int val = st0.size() ? (x - (*prev(st0.end())).first + 1) / 2 : 1e18;
        ans[x] = min(ans[x], val);
        for (auto [t, tim] : l2[x]) {
            if (t == -1) {
                vals[tim] = {x, tim};
                st0.insert({x, tim});
            }
            else {
                st0.erase(vals[tim]);
            }
            val = st0.size() ? (x - (*prev(st0.end())).first + 1) / 2 : 1e18;
            ans[x] = min(ans[x], val);
        }
        if (x <= mxtk) ans[x] = 0;

    }
    while (q--) {
        int ki; cin >> ki;
        cout << ans[ki] << "\n";
    }

}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(9);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}


