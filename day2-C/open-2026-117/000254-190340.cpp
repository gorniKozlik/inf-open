#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define sz(x) (int) x.size()
#define all(x) x.begin(), x.end()
#define int long long

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a.pb({l, 0});
        a.pb({r, 1});
    }
    sort(all(a));
    int pred = 0, kol = 0;
    vector<int> g(n + 1);
    for (auto it : a) {
        if (it.second == 0) {
            kol++;
            int sl = n - pred - kol;
            int ind = kol + min(sl, pred) * 2;
            g[ind] = max(g[ind], kol);
        } else {
            kol--;
            pred++;
        }
    }
    vector<int> ans(n + 1, -1);
    int tek = -1;
    for (int i = n; i >= 1; --i) {
        tek = max(tek, g[i]);
        ans[i] = (i <= tek ? 0 : (i - tek + 1) / 2);
    }
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == -1) {
            ans[i] = ans[i - 1] + 1;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    return 0;
}