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
    vector<int> ans(n + 1, 1e9);
    vector<pair<int, int> > a(n);
    for (auto &[l, r]: a) cin >> l >> r;
    vector<int> l;
    vector<int> r;
    vector<int> cor;
    for (int i = 0; i < n; ++i) {
        l.push_back(a[i].first);
        r.push_back(a[i].second);
        cor.push_back(a[i].first);
        cor.push_back(a[i].second);
    }
    sort(all(a));
    sort(all(l));
    sort(all(r));
    sort(all(cor));
    for (int i = 0; i < 2 * n; ++i) {
        int x = cor[i];
        int left = (int) l.size() - (int) (upper_bound(all(l), x) - l.begin());
        int right = upper_bound(all(r), x) - r.begin();
        int sz = n - left - right;
        ans[sz] = 0;
        int t = min(left, right);
        int s = 1;
        while (t--) {
            ans[sz + 2 * s - 1] = min(ans[sz + 2 * s - 1], s + 1);
            ans[sz + 2 * s] = min(ans[sz + 2 * s], s);
            s++;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
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
