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
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        b.push_back(a[i].first);
        b.push_back(a[i].second);
    }
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    map<int, int> m;
    for (int i = 0; i < len(b); ++i) {
        m[b[i]] = i;
    }
    vector<int> ind(2 * n);
    vector<bool> isleft(2 * n, false);
    int kol = 0;
    for (int i = 0; i < n; ++i) {
        a[i].first = m[a[i].first];
        a[i].second = m[a[i].second];
        ind[a[i].first] = i;
        ind[a[i].second] = i;
        if (a[i].first < n && a[i].second < n) kol++;
        if (a[i].first >= n && a[i].second >= n) kol++;
    }
    int k;
    cin >> k;
    cout << (kol + 1) / 2;
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