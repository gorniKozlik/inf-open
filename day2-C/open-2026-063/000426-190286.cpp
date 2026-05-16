#include<bits/stdc++.h>
#define int long long
using namespace std;

const int INF = 1e18;

map<int, int> mp;

signed main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> el(n);
    vector<pair<int, int>> ids;
    for (int i = 0; i < n; i++) {
        cin >> el[i].first >> el[i].second;
        ids.push_back({el[i].first, -1});
        ids.push_back({el[i].second, 1});
    }
    sort(ids.begin(), ids.end());
    vector<int> ans(n + 1, INF);
    vector<vector<int>> add(n + 2), del(n + 2);
    int mxz = -1;
    int cl = 0, cr = n;
    for (int i = 1; i < (int)ids.size(); i++) {
        if (ids[i - 1].second == -1) {
            cr--;
        } else {
            cl++;
        }
        // for (int j = 0; j <= n - cl - cr; j++) {
        //     ans[j] = 0;
        // }
        mxz = max(mxz, n - cl - cr);
        // for (int j = n - cl - cr + 1; j <= min(n, n - cl - cr + 2 * min(cl, cr)); j++) {
        //     ans[j] = min(ans[j], (j - (n - cl - cr) + 1) / 2);
        // }
        if (n - cl - cr + 1 <= min(n, n - cl - cr + 2 * min(cl, cr))) {
            add[n - cl - cr + 1].push_back(n - cl - cr);
            del[min(n, n - cl - cr + 2 * min(cl, cr)) + 1].push_back(n - cl - cr);
        }
    }
    // exit(0);
    multiset<int> st;
    for (int i = 0; i <= n; i++) {
        for (auto u : del[i]) {
            // cout << i << ' ' << u << endl;
            st.erase(st.find(u));
        }
        for (auto u : add[i]) {
            // cout << i << ' ' << u << endl;
            st.insert(u);
        }
        if (!st.empty()) {
            ans[i] = min(ans[i], (i - *st.rbegin() + 1) / 2);
        }
    }
    for (int i=  0; i <= mxz; i++) {
        ans[i] = 0;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << '\n';
    }
}