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
    vector<int> pt;
    for (auto &u : a) {
        cin >> u.first >> u.second;
        pt.pb(u.first);
        pt.pb(u.second);
    }
    vector<int> ans(n + 1, 1e18);
    sort(all(pt));
    for (auto &e : pt) {
        int lt, rt, canlt, canrt;
        lt = rt = canlt = canrt = 0;
        int gd = 0;
        for (auto &u : a) {
            if (u.first <= e && e <= u.second) {
                gd++;
            }
            if (u.second < e) {
                rt++;
            } else if (u.second == e) {
                canlt++;
            }
            if (u.first > e) {
                lt++;
            } else if (u.first == e) {
                canrt++;
            }
        }
        ans[gd] = 0;
        int calc = gd;
        int res = 0;
        while (lt && rt) {
            calc += 2;
            res++;
            ans[calc] = res;
            lt--;
            rt--;
        }
        while (lt && canlt) {
            calc++;
            res++;
            ans[calc] = res;
            lt--;
            canlt--;
        }
        while (rt && canrt) {
            calc++;
            res++;
            ans[calc] = res;
            rt--;
            canrt--;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i + 1], ans[i]);
        assert(ans[i] != 1e18);
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