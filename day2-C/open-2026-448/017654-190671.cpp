#include<bits/stdc++.h>

using namespace std;

#define int long long

const int eps = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> x;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        x.insert({a[i].first, i});
        x.insert({a[i].second, i});
    }
    int pos = 1;
    for (auto p : x) {
        if (a[p.second].first == p.first) {
            a[p.second].first = pos;
        }
        else {
            a[p.second].second = pos;
        }
        pos += 1;
    }
    for (int i = 0; i < q; i++) {
        int f;
        cin >> f;
        cout << f / 2 << " ";
    }

}

signed main() {
    int t = 1;
    while(t--) {
        solve();
    }
}
