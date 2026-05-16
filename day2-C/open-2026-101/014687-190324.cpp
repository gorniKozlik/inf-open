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
    for (auto &e : pt) {
        gd += sz(enter[e]);
        lt -= sz(enter[e]);
        int tmpLT = lt;
        int tmpRT = rt;
        int canrt = sz(enter[e]);
        int canlt = sz(exit[e]);
        ans[gd] = min(ans[gd], 0ll);
        int calc = gd;
        int res = 0;
        // gd...gd + min(lt, rt) * 2 -> + 1 i += 2
        while (lt && rt) {
            calc += 2;
            res++;
            ans[calc] = min(ans[calc], res);
            if (calc > 10) {
                break;
            }
            lt--;
            rt--;
        }
        // gd + min(lt, rt) * 2 ... gd + min(lt, canlt) -> + 1 i++
        while (lt && canlt) {
            calc++;
            res++;
            ans[calc] = min(ans[calc], res);
            if (calc > 10) {
                break;
            }
            lt--;
            canlt--;
        }
        // gd + min(lt, rt) * 2
        while (rt && canrt) {
            calc++;
            res++;
            ans[calc] = min(ans[calc], res);
            if (calc > 10) {
                break;
            }
            rt--;
            canrt--;
        }
        lt = tmpLT;
        rt = tmpRT;
        gd -= sz(exit[e]);
        rt += sz(exit[e]);
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i + 1], ans[i]);
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