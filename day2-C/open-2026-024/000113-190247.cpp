#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()

void solve() {
    int n, q; cin >>n  >> q;
    vector<int> l(n), r(n);
    for (int j = 0; j < n; j++) cin >> l[j] >> r[j];
    vector<int> ax = l;
    for (int u : r) ax.pb(u);
    sort(all(ax));
    map<int, int> ps;
    for (int j = 0; j < sz(ax); j++) ps[ax[j]] = j;

    for (int j = 0; j < n; j++) {
        l[j] = ps[l[j]];
        r[j] = ps[r[j]];
    }

    vector<int> isr(2 * n);
    for(int u : r) isr[u] = 1;

    vector<int> prefr(2 * n), suffl(2 * n);
    for(int j = 0; j < 2 * n; j++) {
        prefr[j] = isr[j];
        if (j > 0) prefr[j] += prefr[j - 1];
    }

    for (int j = 2 *n  -1; j >= 0; j--) {
        suffl[j]= 1 - isr[j];
        if (j + 1 < sz(suffl)) suffl[j] += suffl[j + 1];
    }

    vector<vector<pair<int, int>>> ev(n + 1);

    for (int i = 0; i < 2 * n -1 ; i++) {
        int have = n - prefr[i] - suffl[i + 1];
        int dop = min(prefr[i], suffl[i + 1]);
        ev[have].pb({have, 1});
        ev[have + 2 * dop + 1].pb({have, -1});
    }
    vector<int> ans(n + 1, 1e9);
    multiset<int> hv;
    for(int j = 0; j <= n; j++) {
        for(auto [x, tp] : ev[j]) {
            if (tp == 1) hv.insert(x);
            else hv.erase(hv.find(x));
        }
        if (!hv.empty()) {
            int hg= *hv.rbegin();
            ans[j] = (j - hg + 1) / 2;
        }
    }
    for(int x = n - 1; x >= 0; x--) ans[x] = min(ans[x], ans[x + 1]);
    while(q--){
        int x; cin >>x; cout<< ans[x] << '\n';
    }
}

signed main() {
    int t = 1;
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        // cin >> t;
    #else 
        cin.tie(0)->sync_with_stdio(false);
    #endif 

    while (t--) solve();

    return 0;
}