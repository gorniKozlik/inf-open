#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

void solve() {
    int n, q;
    cin >> n >> q;

    struct node {
        int x, j;
    };
    vector<node> a;
    a.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;

        a.emplace_back(l - 1, i);
        a.emplace_back(r, i);
    }
    sort(a.begin(), a.end(), [&](node a, node b) {
        return a.x < b.x;
    });

    vector<int> cnt(n), res(n + 1, 1e9);
    int sum = 0, left = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (cnt[a[i].j] == 0) sum++, cnt[a[i].j] = 1;
        else sum--, left++, cnt[a[i].j] = 2;

        while (i + 1 < 2 * n && a[i].x == a[i + 1].x) {
            i++;
            if (cnt[a[i].j] == 0) sum++, cnt[a[i].j] = 1;
            else sum--, left++, cnt[a[i].j] = 2;
        }

        int d = min(left, n - left - sum);
        for (int j = 0; j <= d; ++j) {
            res[sum + 2 * j] = min(res[sum + 2 * j], j);
        }
        for (int j = 0; j <= min(sum, n - 2 * d - sum); ++j) {
            res[sum + 2 * d + j] = min(res[sum + 2 * d + j], d + j);
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        res[i] = min(res[i], res[i + 1]);
    }

    while (q--) {
        int k;
        cin >> k;

        cout << res[k] << " ";
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}