#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define f first
#define s second
#define ll long long
#define ld long double
#define pii pair<int, int>

using namespace std;

int getcnt(set<pii> v) {
    set<pii> s;
    int mx = 0;
    for (auto [l, r] : v) {
        while (true) {
            if (s.empty()) break;
            auto [qr, ql] = *s.begin();
            if (qr >= l) break;
            s.erase(s.begin());
        }
        s.insert({r, l});
        mx = max((int) s.size(), mx);
    }
    return mx;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].f >> v[i].s;
    }
    set<pii> por, pol;
    for (auto [l, r] : v) {
        pol.insert({l, r});
        por.insert({r, l});
    }
    vector<int> ans(n + 1, 0);
    set<pii> s;
    for (auto [l, r] : v) {
        s.insert({l, r});
    }
    int cnt = getcnt(s);
    for (int i = 1; i <= cnt; i++) ans[i] = 0;
    int cur = 0;
    while (true) {
        auto [ar, al] = *por.begin();
        auto [bl, br] = *pol.rbegin();
        por.erase({ar, al});
        por.erase({br, bl});
        pol.erase({bl, br});
        pol.erase({al, ar});
        s.erase({al, ar});
        s.erase({bl, br});
        int nl = al, nr = bl;
        int ml = ar, mr = br;
        pol.insert({nl, nr});
        pol.insert({ml, mr});
        por.insert({nr, nl});
        por.insert({mr, ml});
        s.insert({nl, nr});
        s.insert({ml, mr});
        int ncnt = getcnt(s);
        cur++;
        for (int i = cnt + 1; i <= ncnt; i++) ans[i] = cur;
        cnt = ncnt;
        if (ncnt == n) break;
    }
    while (q--) {
        int cnt; cin >> cnt;
        cout << ans[cnt] << " ";
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}