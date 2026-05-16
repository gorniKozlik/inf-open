#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define int ll

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

const int inf = 2e9, INF = 1e18;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> op(2 * n), cl(2 * n);
    vector<pii> al;
    vector<int> k;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        k.push_back(l);
        k.push_back(r);
        // k.push_back(r + 1);
        // k.push_back(l - 1);
        al.emplace_back(l, r);
    }
    op.resize(k.size());
    cl.resize(k.size());
    sort(all(k));
    k.resize(unique(all(k)) - k.begin());
    for (auto &[l, r]: al) {
        l = lower_bound(all(k), l) - k.begin();
        r = lower_bound(all(k), r) - k.begin();
#ifdef LOCAL
        cout << l << " " << r << "\n";
#endif

        op[l]++;
        if (r < cl.size())
            cl[r]++;
    }
    int cnt = 0, cnt1 = 0;
    int ans = 0;
    vector<int> ans1(n + 1, inf);
    vector<vector<pii> > sl(n + 2);
    for (int i = 0; i < op.size(); i++) {
        cnt -= cl[i];
        cnt1 += cl[i];
        sl[cnt].emplace_back(cnt, 1);
        sl[cnt + 2 * min(cnt1, (n - cnt - cnt1)) + 1].emplace_back(cnt, -1);
        // for (int i = cnt; i <= cnt + 2 * min(cnt1, (n - cnt - cnt1)); i++) ans1[i] = min(ans1[i], (i - cnt + 1) / 2);
        cnt += op[i];
        sl[cnt].emplace_back(cnt, 1);
        sl[cnt + 2 * min(cnt1, (n - cnt - cnt1)) + 1].emplace_back(cnt, -1);
        // for (int i = cnt; i <= cnt + 2 * min(cnt1, (n - cnt - cnt1)); i++) ans1[i] = min(ans1[i], (i - cnt + 1) / 2);
    }
    multiset<int> s;
    for (int i = 0; i <= n; i++) {
        for (auto &[j, t]: sl[i]) {
            if (t == 1) {
                s.insert(j);
            } else {
                s.erase(s.find(j));
            }
        }
        ans1[i] = (i - *s.rbegin() + 1) / 2;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans1[k] << " ";
    }
}

int32_t main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
    }
}
