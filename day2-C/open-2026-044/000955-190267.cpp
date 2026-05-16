#include <bits/stdc++.h>


using namespace std;

using ll = long long;
using pii = pair<int, int>;
using namespace std;
const ll mod = 998244353;



signed main() {
#ifdef LOCAL
    freopen("input", "r", stdin);
#else
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int n, q;
    cin >> n >> q;
    vector<pii> otr(n);
    vector<int> crd;
    for (int i = 0; i < n; i++) {
        cin >> otr[i].first >> otr[i].second;
        crd.push_back(otr[i].first);
        crd.push_back(otr[i].second);
    }
    vector<int> b(2 * n, 0);
    sort(crd.begin(), crd.end());
    for (int i = 0; i < n; i++) {
       //out << (lower_bound(crd.begin(), crd.end(), otr[i].first) - crd.begin()) << endl;
        b[lower_bound(crd.begin(), crd.end(), otr[i].first) - crd.begin()]++;
        b[lower_bound(crd.begin(), crd.end(), otr[i].second) - crd.begin()]--;
    }

    int t = 0;
    vector<int> ans(n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        if (b[i] == 1) {
            t++;
            ans[min(i + 1, 2 * n - i)] = max(t, ans[min(i + 1, 2 * n - i)] );
        } else {
            ans[min(i + 1, 2 * n - i)] = max(t, ans[min(i + 1, 2 * n - i)]);
            t--;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    // for (int i: ans) {
    //     cout << i << endl;
    // }
    while (q--) {
        int k;
        cin >> k;
        cout << ((max(k - ans[k], 0) + 1) / 2) << " ";
    }
    
}