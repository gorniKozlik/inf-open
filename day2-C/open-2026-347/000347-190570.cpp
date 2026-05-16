#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

struct str {
    int l;
    int r;
    int ind;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v;
    vector<int> p;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
        p.push_back(a);
        p.push_back(b);
    }
    vector<int> ask(q);
    for (int i = 0; i < q; ++i) cin >> ask[i];
    sort(all(p));
    int ans = 0;
    int t = p[n - 1];
    for (int i = 0; i < n; ++i) {
        if (v[i].ff < t && v[i].ss < t) {
            ans += 1;
        }
        if (v[i].ff > t && v[i].ss > t) {
            ans += 1;
        }
    }
    cout << (ans + 1) / 2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int t = 1;
    while (t--) solve();
}
