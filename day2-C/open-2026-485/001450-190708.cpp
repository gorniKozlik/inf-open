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
        A.push_back({l, r});
    }
    sort(A.begin(), A.end());
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k == 1) {
            cout << 0 << " ";
            continue;
        }
        if (k == n) {
            cout << n / 2 << " ";
            continue;
        }
        if (k % 2 == 0) {
            cout << k / 2 << " ";
            continue;
        }
        cout << (k / 2) << " ";
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
