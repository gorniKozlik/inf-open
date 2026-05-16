#include <bits/stdc++.h>

#define int long long

using namespace std;

constexpr int N = 2e5 + 10, L = 20;

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int> > a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.emplace(x, 1);
        a.emplace(y, -1);
    }
    vector<int> b;
    for (auto [x, t]: a) {
        if (t == 1) {
            b.push_back(1);
        } else {
            b.push_back(-1);
        }
    }
    int prefix[2 * n];
    prefix[0] = b[0];
    for (int i = 1; i < 2 * n; ++i) {
        prefix[i] = prefix[i - 1] + b[i];
    }
    int mx[L][2 * n];
    int ind = 1;
    for (int i = 0; i < 2 * n; ++i) {
        mx[0][i] = prefix[i];
        ind = max(ind, prefix[i]);
    }
    for (int i = 1; i < L; ++i) {
        for (int j = 0; j + (1 << i) < 2 * n; ++j) {
            mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
        }
    }
    vector<int> ans(n + 1);
    for (int i = 1; i <= ind; ++i) {
        ans[i] = 0;
    }
    ind++;
    int i = 0, j = 2 * n - 1;
    int cnt = 0;
    while (i < j) {
        while (i < 2 * n && b[i] == 1) {
            i++;
        }
        while (j >= 0 && b[j] == -1) {
            j--;
        }
        if (i > j) break;
        cnt++;
        if (i + 1 == j) {
            for (int k = ind; k <= n; ++k) {
                ans[k] = cnt;
            }
        } else {
            int d = __lg(j - i - 1);
            int next = max(mx[d][i + 1], mx[d][j - 1 - (1 << d) + 1]) + 2 * cnt;
            for (int k = ind; k <= next; ++k) {
                ans[k] = cnt;
            }
            ind = next + 1;
        }
        i++, j--;
    }
    for (int k = ind; k <= n; ++k) {
        ans[k] = cnt;
    }
    for (int e = 0; e < q; ++e) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int dota = 1;
    //cin >> dota;
    while (dota--) {
        solve();
        cout << '\n';
    }
    return 0;
}
