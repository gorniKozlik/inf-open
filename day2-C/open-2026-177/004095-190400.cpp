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
    for (int i = 0; i < n; ++i) {
        a[i].first = m[a[i].first];
        a[i].second = m[a[i].second];
    }
    vector<int> anses(n + 1, 1e9);
    for (int i = 0; i < 2 * n; ++i) {
        int now = 0;
        for (int j = 0; j < n; ++j) {
            if (a[j].first < i && a[j].second >= i) {
                now++;
            }
        }
        for (int j = 0; j <= n; ++j) {
            if (j <= now) {
                anses[j] = 0;
            } else {
                anses[j] = min(anses[j], (j - now + 1) / 2);
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << anses[k] << " ";
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