#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define f first
#define s second
#define ll long long
#define ld long double
#define pii pair<int, int>

using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].f >> v[i].s;
    }
    sort(v.begin(), v.end());
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
    s.clear();
    for (auto [l, r] : v) {
        while (true) {
            if (s.empty()) break;
            auto [qr, ql] = *s.begin();
            if (qr >= l) break;
            s.erase(s.begin());
        }
        s.insert({r, l});
        if (mx == (int) s.size()) break;
    }
    set<pii> in;
    for (auto [l, r] : s) {
        in.insert({r, l});
    }
    set<pii> por, pol;
    for (auto [l, r] : v) {
        pol.insert({l, r});
        por.insert({r, l});
    }
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= mx; i++) {
        ans[i] = 0;
    }
    int cur = (int) in.size();
    int cnt = 0;
    while (true) {
        auto [ar, al] = *por.begin();
        auto [bl, br] = *pol.rbegin();
        por.erase({ar, al});
        pol.erase({bl, br});
        int nl = al, nr = bl;
        int ml = ar, mr = br;
        if (in.find({al, ar}) != in.end() || in.find({bl, br}) != in.end()) {
            cnt++;
            cur += 1;
            ans[cur] = cnt;
        } else {
            cnt++;
            cur += 2;
            ans[cur] = cnt;
            ans[cur - 1] = cnt;
        }
        if (in.find({al, ar}) != in.end()) {
            in.erase({al, ar});
        }
        if (in.find({bl, br}) != in.end()) {
            in.erase({bl, br});
        }
        in.insert({nl, nr});
        in.insert({ml, mr});
        if (cur == n) break;
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