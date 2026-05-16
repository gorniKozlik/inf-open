#pragma GCC optimize("O3,unroll-loops")
#include<bits/extc++.h>
#pragma GCC target("avx2,popcnt")

#define all(_a) _a.begin(), _a.end()
#define sz(_a) int32_t(_a.size())
#define ll long long
// #define int long long
#define fi first
#define se second
#define deb(_a) cerr << __LINE__ << ' ' << (#_a) << ": " << _a << '\n';

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto i: v) out << i << ' ';
    return out;
}

template<typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (auto &i: v) in >> i;
    return in;
}

inline void solve();

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.se < b.se;
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v, s, k(m);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.emplace_back(x, 1);
        v.emplace_back(y, -1);
    }
    for (int i = 0; i < m; i++) {
        cin >> k[i].fi;
        k[i].se = i;
    }
    sort(all(v));
    sort(all(k));
    int a = 0, cur = 0, mx = 0;
    vector<int> rs;
    for (int i = 0; i < 2 * n - 1; i++) {
        cur += v[i].se;
        if (v[i].se == -1) a++;
        int b = n - a - cur;

        mx = max(mx, cur);
        s.push_back({cur, cur + 2 * min(a, b)});
        rs.emplace_back(cur + 2 * min(a, b));
    }
    sort(all(s), cmp);
    // for (auto [l, r]: s) cout << l << ' ' << r << '\n';
    vector<int> ans(m, 1e9);
    for (int i = 0; i < m; i++) {
        if (k[i].fi <= mx) ans[k[i].se] = 0;
    }
    // for (auto i: ans) cout << i << ' ';
    // cout << '\n';
    set<int> st;
    int ind = sz(k) - 1;
    while (ind >= 0 && k[ind].fi > s.back().se) {
        ind--;
    }
    for (int i = sz(s) - 1; i >= 0; i--) {
        while (ind >= 0 && k[ind].fi > s[i].se) {
            auto it = st.upper_bound(k[ind].fi);
            if (it != st.begin()) {
                int t = *(--it);
                // cerr << k[ind].fi << ' ' << t << '\n';
                ans[k[ind].se] = min(ans[k[ind].se], (k[ind].fi - t + 1) / 2);
            }
            ind--;
        }
        st.insert(s[i].fi);
    }
    for (auto i: ans) cout << i << ' ';
}