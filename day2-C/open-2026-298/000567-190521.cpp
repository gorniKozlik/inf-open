#include <bits/stdc++.h>
using namespace std;
#define int long long

void solution();

signed main() {
#ifdef LOCAL
    freopen("test", "r", stdin);
    freopen("res", "w", stdout);
#endif

    solution();
}

const int lg = 20;

void solution() {
    int n, q;
    cin >> n >> q;

    vector<int> l(n), r(n), xs;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        xs.push_back(l[i]);
        xs.push_back(r[i]);
    }

    sort(xs.begin(), xs.end());
    for (auto &x : l) {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    for (auto &x : r) {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    vector<vector<int>> st(lg, vector<int>(n * 2));
    vector<int> dp(n * 2 + 1);
    for (int i = 2; i <= n * 2; ++i) {
        dp[i] = dp[i >> 1] + 1;
    }

    vector<int> a(n * 2);
    int curl = 0, curr = 0;
    int cur = 0;
    for (int i = 0; i < n * 2; ++i) {
        if (curl < n && l[curl] == i) {
            a[i] = ++cur;
            curl++;
        } else {
            a[i] = --cur;
            curr++;
        }
    }

    vector<int> ans(n + 1, -1);
    int k0 = *max_element(a.begin(), a.end());
    for (int i = k0; i >= 0; --i) {
        ans[i] = 0;
    }
    
    st[0] = a;
    for (int j = 1; j < lg; ++j) {
        for (int i = 0; i + (1 << j) <= n * 2; ++i) {
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }

    int mx = k0;
    cur = 0;
    for (int i = 0; i < n; ++i) {
        if (r[i] > l[n - i - 1]) break;
        cur += 2;
        int sz = dp[l[n - i - 1] - r[i]];
        int ki = max(st[sz][r[i]], st[sz][l[n - i - 1] - (1 << sz)]) + cur;
        mx = max(ki, mx);
        for (int j = mx; j >= 0; --j) {
            if (ans[j] != -1) break;
            ans[j] = i + 1;
        }
    }

    while (q--) {
        int k;
        cin >> k;

        cout << ans[k] << ' ';
    }
    cout << '\n';
}