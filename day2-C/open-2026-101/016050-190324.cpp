#include <bits/stdc++.h>
using namespace std;

#define line cout << "\n"
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define sz(a) (int) a.size()
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pii pair<int, int>

typedef string str;
typedef long long ll;
typedef long double ld;
const int MAXN = 2e5 + 10;
vector<int> dp2_enter[MAXN], dp2_exit[MAXN];
vector<pii> dp1_enter[MAXN], dp1_exit[MAXN];
pii a[MAXN];
int ans[MAXN];

void solve() {
    int n, q;
    cin >> n >> q;
    set<int> pt;
    map<int, vector<int>> enter, exit;
    vector<pii> a(n);
    for (auto &u : a) {
        cin >> u.first >> u.second;
        enter[u.first].pb(u.second);
        exit[u.second].pb(u.first);
        pt.insert(u.first);
        pt.insert(u.second);
    }
    for (int i = 0; i <= n; i++) {
        ans[i] = 1e9;
    }
    int gd = 0;
    int lt = n, rt = 0;
    for (auto &e : pt) {
        gd += sz(enter[e]);
        lt -= sz(enter[e]);
        int canrt = sz(enter[e]);
        int canlt = sz(exit[e]);
        ans[gd] = min(ans[gd], 0);
        int calc = gd;
        // gd...gd + min(lt, rt) * 2 -> + 1 i += 2
        int lft = gd + min(lt, rt) * 2;
        dp2_enter[gd].pb(gd);
        dp2_exit[lft].pb(gd);
        int res = min(lt, rt);
         // gd + min(lt, rt) * 2 ... gd + min(lt, canlt) -> + 1 i++
        int rft = lft + min(lt - min(lt, rt), canlt);
        if (lft != rft) {
            dp1_enter[lft].pb({lft, res});
            dp1_exit[rft].pb({lft, res});
        }
        // gd + min(lt, rt) * 2
        rft = lft + min(rt - min(lt, rt), canrt);
        if (lft != rft) {
            dp1_enter[lft].pb({lft, res});
            dp1_exit[rft].pb({lft, res});
        }
        gd -= sz(exit[e]);
        rt += sz(exit[e]);
    }
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    multiset<int> st1, st2;
    for (int i = 0; i <= n; i++) {
        if (sz(st2)) {
            auto it = --st2.end();
            ans[i] = min(ans[i], (i - *it + 1) / 2);
        }
        if (sz(st1)) {
            auto it = st1.begin();
            ans[i] = min(ans[i], *it + i);
        }
        for (auto &u : dp2_enter[i]) {
            st2.insert(u);
        }
        for (auto &u : dp2_exit[i]) {
            st2.erase(st2.find(u));
        }
        for (auto &u : dp1_enter[i]) {
            st1.insert({u.second - i});
        }
        for (auto &u : dp1_exit[i]) {
            st1.erase(st1.find(u.second - u.first));
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}