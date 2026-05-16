#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
#define asc(x) x.begin(), x.end()
#define des(x) x.rbegin(), x.rend()
#define pb push_back
#define eb emplace_back
#define ll long long
#define db long double
#define fori(a, b) for (int i = (a); i < (b); ++i)
#define forj(a, b) for (int j = (a); j < (b); ++j)

using namespace std;
// using namespace __gnu_pbds;
// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 gen(228);

void solve() {
    int n, q; cin >> n >> q;

    vector<pair<int, int>> a(n);
    vector<int> p; p.reserve(2 * n);

    fori(0, n) {
        cin >> a[i].first >> a[i].second;

        p.pb(a[i].first);
        p.pb(a[i].second);
    }

    sort(asc(p));

    p.erase(unique(asc(p)), p.end());

    unordered_map<int, int> mp;

    fori(0, p.size()) {
        mp[p[i]] = i;
    }

    vector<int> c1(2 * n + 2, 0), c2(2 * n + 2, 0);

    fori(0, n) {
        a[i].first = mp[a[i].first];
        a[i].second = mp[a[i].second];

        c1[a[i].first]++;
        c2[a[i].second]++;
    }

    vector<int> ans(n + 1, n);
    vector<int> go(n + 1, 0);
    vector<vector<int>> dlt(2 * n + 1);

    int mx = 1;

    ans[0] = 0;

    int cnt1 = 0, cnt2 = 0;
    fori(0, 2 * n) {
        cnt1 += c1[i];

        mx = max(mx, cnt1);

        int can = min(cnt2, n - cnt1 - cnt2);

        go[cnt1] = max(go[cnt1], can);

        cnt1 -= c2[i];
        cnt2 += c2[i];
    }

    fori(1, mx + 1) {
        ans[i] = 0;

        if (go[i]) {
            dlt[2 * go[i] + i + 1].pb(i);
        }
    }

    set<int> have;
    fori(1, n + 1) {
        if (go[i]) {
            have.insert(i);
        }

        for (int x : dlt[i]) {
            have.erase(x);
        }

        ans[i] = min(ans[i], ans[i - 1] + 1);

        if (!have.empty()) {
            int j = *have.rbegin();

            ans[i] = min(ans[i], (i - j + 1) / 2);
        }
    }

    while (q--) {
        int x; cin >> x;

        cout << ans[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int tt = 1;
    while (tt--) {
        solve();
        cout << "\n";
    }
}