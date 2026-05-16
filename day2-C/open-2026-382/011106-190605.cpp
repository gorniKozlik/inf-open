#include <bits/stdc++.h>
#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ff first
#define ss second

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> a(n);
    vector <pair <int, int>> b(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].ff >> a[i].ss;
        b[i] = {a[i].ff, 0};
        b[n + i] = {a[i].ss, 1};
    }
    sort(all(b));
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += b[i].ss;
    }
    while (q--) {
        int k;
        cin >> k;
        if (k != n) {
            cout << k / 2 << ' ';
        } else {
            cout << cnt << ' ';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t = 1;
    while (t--) solve(), cout << '\n';
}
