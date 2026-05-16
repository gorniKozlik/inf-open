#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

void fast_in_out() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(18) << fixed;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
}

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define all(x) (x).begin(), (x).end()
#define int long long
using ll = long long;
const int N = 2e5, inf = 1e18;
int n, q, ans[N + 1], ans1[N + 1], ans2[N + 1];
pair<int, int> a[N];
vector<tuple<int, int, int> > b;

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        b.emplace_back(a[i].first, -1, i);
        b.emplace_back(a[i].second, 1, i);
    }
    sort(all(b));
    int l = 0, r = 0, cnt = 0;
    vector<tuple<int, int, int> > vec;
    for (int i = 0; i <= n; ++i) {
        ans1[i] = n;
        ans2[i] = inf;
        ans[i] = n;
    }
    int mx = 0;
    for (auto [x, type, pos]: b) {
        if (type == 1) {
            --cnt;
            ++l;
        } else {
            ++cnt;
            r = n - l - cnt;
            vec.emplace_back(l, cnt, r);
            mx = max(mx, cnt);
            ans1[cnt + 2 * min(l, r) + 1] = min(ans1[cnt + 2 * min(l, r) + 1], min(l, r) + 1);
            ans2[cnt + 2 * min(l, r)] = min(ans2[cnt + 2 * min(l, r)], min(l, r));
            ans2[cnt + 2 * min(l, r) - 1] = min(ans2[cnt + 2 * min(l, r) - 1], min(l, r));
        }
    }
    cnt = n;
    int cnt0 = inf, cnt1 = inf;
    for (int i = 1; i <= n; ++i) {
        ++cnt;
        cnt = min(cnt, ans1[i]);
        if (i <= mx) {
            ans[i] = 0;
        }
        ans[i] = min(ans[i], cnt);
    }
    for (int i = n; i > mx; --i) {
        if (i % 2 == 0) {
            cnt0--;
            cnt0 = min(cnt0, ans2[i]);
            ans[i] = min(ans[i], cnt0);
        } else {
            cnt1--;
            cnt1 = min(cnt1, ans2[i]);
            ans[i] = min(ans[i], cnt1);
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

signed main() {
    fast_in_out();
    int qwe = 1;
    // cin >> qwe;
    while (qwe--) {
        solve();
    }
}
