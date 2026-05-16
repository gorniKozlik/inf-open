#include <bits/stdc++.h>

//#pragma GCC optimize("O3", "unroll-loops")

#define int long long
#define ll long long
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
#define ff first
#define ss second

using namespace std;

const int mod = 998244353;

int bin_pow(int x, int k) {
    if (k == 0) {
        return 1;
    }
    if (k % 2 == 0) {
        int bp = bin_pow(x, k / 2);
        return (bp * bp) % mod;
    }
    return (bin_pow(x, k - 1) * x) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<pii> p;
    for (int i = 0; i < n; ++i ) {
        int l, r; cin >> l >> r;
        p.emplace_back(l, 0);
        p.emplace_back(r, 1);
    }
    sort(all(p));
    int cur = 0;
    int j =0;
    vector<int> ans(n, 1e9);
    for (int i = 0; i < n; ++i) {
        ans[i] = i;
    }
    for (int i = 0; i < 2 * n; ++i) {
        if (p[i].ss == 0) {
            cur++;
        } else {
            cur--;
        }
        for (; j < min(i + 1, 2 * n - i - 1); ++j) {
            ans[j] = min(ans[j], (min(i + 1, 2 * n - i - 1) - cur + 1) / 2);
        }
        if (cur > 0)
            ans[cur - 1] = 0;
    }
    for (int i = 0; i < q; ++i) {
        int req; cin >> req;
        cout << ans[req - 1] << ' ';
    }
}

