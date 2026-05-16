#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> nits(n);
    for (int i = 0; i < n; i++) {
        cin >> nits[i].first >> nits[i].second;
    }

    while (q--) {
        cout << (q + 1) / 2 << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}