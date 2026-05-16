#include <bits/stdc++.h>
using namespace std;


#define int long long
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


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    set<int> pt;
    map<int, vector<int>> enter, exit;
    for (auto &u : a) {
        cin >> u.first >> u.second;
        enter[u.first].pb(u.second);
        exit[u.second].pb(u.first);
        pt.insert(u.first);
        pt.insert(u.second);
    }
    vector<int> ans(n + 1, 1e18);
    int gd = 0;
    int lt = n, rt = 0;
    vector<int> can_go2(n + 1);
    vector<int> can_go1(n + 1);
    for (auto &e : pt) {
        gd += sz(enter[e]);
        lt -= sz(enter[e]);
        int tmpLT = lt;
        int tmpRT = rt;
        int canrt = sz(enter[e]);
        int canlt = sz(exit[e]);
        ans[gd] = min(ans[gd], 0ll);
        int calc = gd;
        // gd...gd + min(lt, rt) * 2 -> + 1 i += 2
        int lft = gd + min(lt, rt) * 2;
        int res = 0;
        for (int i = gd; i < lft; i += 2) {
            ans[i + 2] = min(ans[i + 2], ++res);
        }
        // gd + min(lt, rt) * 2 ... gd + min(lt, canlt) -> + 1 i++
        int rft = lft + min(lt - min(lt, rt), canlt);
        for (int i = lft; i < rft; i++) {
            ans[i + 1] = min(ans[i + 1], ++res);
        }
        // gd + min(lt, rt) * 2
        rft = lft + min(rt - min(lt, rt), canrt);
        for (int i = lft; i < rft; i++) {
            ans[i + 1] = min(ans[i + 1], ++res);
        }
        gd -= sz(exit[e]);
        rt += sz(exit[e]);
    }
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
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