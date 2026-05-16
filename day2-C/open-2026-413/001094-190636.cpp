#include <bits/stdc++.h>

#define int long long

using namespace std;

constexpr int N = 2e5 + 10;

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> a;
    vector<pair<int, int>> st, en;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.emplace(x, y);
        st.emplace_back(-x, i);
        en.emplace_back(y, i);
    }
    sort(st.begin(), st.end());
    sort(en.begin(), en.end());
    int ans = 0;
    int i = 0, j = 0;
    while (i < n && -st[i].first > en[j].first) {
        ans++;
        i++, j++;
    }
    cout << ans;
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
