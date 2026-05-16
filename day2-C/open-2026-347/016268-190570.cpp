#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
const int INF = 1e9 + 7;
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
    vector<int> ans(n + 1, INF);
    for (int i = 0; i < n * 2; ++i) {
        int t = 0;
        int l = 0;
        int r = 0;
        for (int j = 0; j < n; ++j) {
            if (v[j].ff <= p[i] && v[j].ss >= p[i]) t++;
            if (v[j].ff < p[i] && v[j].ss < p[i]) l++;
            if (v[j].ff > p[i] && v[j].ss > p[i]) r++;
            //if (l >= 10 && r >= 10) break;
        }
        for (int j = 1; j <= min((ll)1e9, n); ++j) {
            if (j - t <= 0) ans[j] = min(ans[j], 0ll);
            else {
                int tmp = t;
                if (tmp + min(l, r) * 2 >= j) ans[j] = min(ans[j], (j - t + 1) / 2);
                else {
                    tmp += min(l, r) * 2;
                    //cout << j << ' ' << tmp << endl;
                    ans[j] = min(ans[j], min(l, r) + (j - tmp));
                }
            }
        }
    }
    vector<int> b;
    while (q--) {
        int k;
        cin >> k;
        b.push_back(ans[k]);
    }
    for (auto i:b) cout << i << ' ';
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    while (t--) solve();
}
