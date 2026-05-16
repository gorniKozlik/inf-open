#include <bits/stdc++.h>

using namespace std;
using ll = long long;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << k / 2 << ' ';
    }
}