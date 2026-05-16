#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ll long long
const int INF = 1e9 + 7;

struct str {
    int x;
    int c;
    int i;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v;
    vector<str> p;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
        p.push_back({a, 0, i});
        p.push_back({b, 1, i});
    }
    sort(all(p), [](auto &a, auto &b){if (a.x != b.x) return a.x < b.x; else return a.c < b.c;});
    vector<int> ans(n + 1, INF);
    sort(all(v));
    int k = 0;
    int z = 0;
    vector<int> l(2 * n, 0);
    vector<int> t(2 * n, 0);
    vector<int> r(2 * n, 0);
    for (int i = 0; i < 2 * n; ++i) {
        if (p[i].c == 0) k++;
        l[i] = z;
        t[i] = k;
        r[i] = (n - k - z) / 2;
        if (p[i].c == 1) k--, z++;
    }
    for (int i = 0; i < n * 2; ++i) {
        int t1 = t[i];
        int l1 = l[i];
        int r1 = r[i];
        for (int j = 1; j <= n; ++j) {
            if (j - t1 <= 0) ans[j] = min(ans[j], 0ll);
            else {
                int tmp = t1;
                if (tmp + min(l1, r1) * 2 >= j) ans[j] = min(ans[j], (j - t1 + 1) / 2);
                else {
                    tmp += min(l1, r1) * 2;
                    //cout << j << ' ' << tmp << endl;
                    ans[j] = min(ans[j], min(l1, r1) + (j - tmp));
                }
            }
        }
    }
    vector<int> b;
    while (q--){
        int x;
        cin >> x;
        b.push_back(ans[x]);
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
