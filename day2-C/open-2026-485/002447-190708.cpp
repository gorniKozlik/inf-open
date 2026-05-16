#include <bits/stdc++.h>
#define int long long

using namespace std;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > A;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        A.push_back({l, 0});
        A.push_back({r, 1});
    }
    sort(A.begin(), A.end());

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int open = 0;
        int kol = 0;
        int ans = 100000000000;
        for (auto j: A) {
            kol++;
            if (j.second == 0) {
                open++;
            }
            if (min(kol, 2 * n - kol) >= k) {
                ans = min(ans, max(0LL, k - open));
            }
            if (j.second == 1) {
                open--;
            }
        }
        cout << ans / 2 + ans % 2 << " ";
    }
    cout << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
