#include<bits/stdc++.h>

using namespace std;

#define int long long

const int eps = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    for (int i = 0; i < q; i++) {
        int f;
        cin >> f;
        cout << 0 << " ";
    }
}

signed main() {
    int t = 1;
    while(t--) {
        solve();
    }
}
