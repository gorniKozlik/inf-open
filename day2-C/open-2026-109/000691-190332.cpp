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
const int N = 2e5;
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
    for (auto [x, type, pos]: b) {
        if (type == 1) {
            --cnt;
            ++l;
        } else {
            ++cnt;
            r = n - l - cnt;
            vec.emplace_back(l, cnt, r);
        }
    }
    // reverse(all(b));
    // l = 0, cnt = 0, r = 0;
    // for (auto [x, type, pos]: b) {
    //     if (type == 1) {
    //         ++cnt;
    //         l = n - r - cnt;
    //         vec.emplace_back(l, cnt, r);
    //     } else {
    //         --cnt;
    //         ++r;
    //     }
    // }
    while (q--) {
        int k;
        cin >> k;
        int f = n;
        for (auto [l1, m, r1]: vec) {
            if (k <= m) {
                f = 0;
            } else if (k <= m + 2 * min(l1, r1)) {
                f = min(f, (k - m + 1) / 2);
            } else {
                f = min(f, k - m - min(l1, r1));
            }
        }
        cout << f << ' ';
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
