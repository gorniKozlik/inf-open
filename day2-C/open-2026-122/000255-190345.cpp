#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif // LOCAL

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using ui = unsigned int;
using ull = unsigned long long;

#define sz(x) (int)x.size()

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    vector<int> crd(n * 2);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        seg[i] = {l, r};
        crd[i * 2] = l;
        crd[i * 2 + 1] = r;
    }
    sort(crd.begin(), crd.end());
    vector<int> d(n * 2);
    for (auto [l, r] : seg) {
        int i = lower_bound(crd.begin(), crd.end(), l) - crd.begin();
        ++d[i];
        i = lower_bound(crd.begin(), crd.end(), r) - crd.begin();
        --d[i];
    }
    vector<int> op(n + 1);
    int cnt = 0;
    for (int i = 0; i + 1 < n * 2; ++i) {
        cnt += d[i];
        int mx = min(i + 1, 2 * n - i - 1);
        op[mx] = max(op[mx], cnt);
    }
    for (int i = n - 1; i > 0; --i) {
        op[i] = max(op[i + 1], op[i]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << max((k - op[k] + 1) / 2, 0) << " ";
    }
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int times = 1;
//    cin >> times;
    while (times--) {
        solve();
    }
    return 0;
}
