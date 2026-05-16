#include<bits/stdc++.h>

#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long int;
using ld = long double;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << (k + 1) / 2 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
}