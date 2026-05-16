#include <bits/stdc++.h>

#define int long long

using namespace std;

constexpr int N = 2e5 + 10, L = 20;

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int> > a;
    vector<int> st, en;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.emplace(x, 1);
        a.emplace(y, -1);
        st.push_back(-x);
        en.push_back(y);
    }
    sort(st.begin(), st.end());
    sort(en.begin(), en.end());
    vector<int> b;
    for (auto [x, t]: a) {
        if (t == 1) {
            b.push_back(1);
        } else {
            b.push_back(-1);
        }
    }
    vector<int> ans(n + 1);
    int ind = 1;
    int mx = 0, cnt = 0;
    for (int k = 0; k < 2 * n; ++k) {
        cnt += b[k];
        mx = max(mx, cnt);
    }
    for (int i = ind; i <= mx; ++i) {
         ans[i] = 0;
    }
    ind = mx + 1;
    int i = 0, j = 2 * n - 1;
    int t = 0;
    while (i < j) {
        while (i < 2 * n && b[i] == 1) {
            i++;
        }
        while (j >= 0 && b[j] == -1) {
            j--;
        }
        if (i > j) break;
        t++;
        b[i] = 1;
        b[j] = -1;
        mx = 0, cnt = 0;
        for (int k = 0; k < 2 * n; ++k) {
            cnt += b[k];
            mx = max(mx, cnt);
        }
        for (int k = ind; k <= mx; ++k) {
            ans[k] = t;
        }
        ind = mx + 1;
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
