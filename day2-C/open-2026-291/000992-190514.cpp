#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
#define all(a) a.begin(), a.end()
const int MOD = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> ans(n, 1e9);
    vector<pair<int, int> > a(n);
    for (auto &[l, r]: a) cin >> l >> r;
    sort(all(a));
    ordered_set<int> s;
    int cnt = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        s.insert(a[i].second);
        cnt = (int) s.size() - s.order_of_key(a[i].first);
        mx = max(mx, cnt);
    }
    ans[mx - 1] = 0;
    set<pair<int, int>> seg;
    for (int i = 0; i < n; ++i) {
        seg.emplace(a[i]);
    }
    for (int _ = 1; _ < n; ++_) {
        pair<int, int> p = {0, 0};
        for (auto [l, r] : seg) {
            if (r > p.second) {
                p = {l, r};
            }
        }
        auto [l, r] = (*seg.begin());
        seg.erase(seg.begin());
        seg.erase(seg.find(p));
        seg.emplace(min(r, p.first), max(r, p.first));
        s.clear();
        cnt = 0;
        mx = 0;
        for (auto [l, r] : seg) {
            s.insert(r);
            cnt = (int) s.size() - s.order_of_key(l);
            mx = max(mx, cnt);
        }
        ans[mx + _ - 1] = min(ans[mx + _ - 1], _);
    }
    for (int i = n - 2; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k - 1] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
