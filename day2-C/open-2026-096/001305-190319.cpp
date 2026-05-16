// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
// #pragma GCC target("avx2")

using namespace std;

const int inf = 1e9;
const int N = 2e5 + 5;

int ans[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int lp = 0, rp = n, in = 0;
    vector<pair<int, int>> event;
    for (int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        event.push_back({l, 0});
        event.push_back({r + 1, 1});
        event.push_back({r, 2});
    }

    sort(event.begin(), event.end());

    for (int i = 1; i <= n; ++i) {
        ans[i] = inf;
    }

    int mx_in = 1;
    vector<int> arifm(n + 1, inf);
    for (auto& [x, y]: event) {
        if (y == 0) --rp, ++in;
        else if (y == 1) ++lp, --in;
        else {
            mx_in = max(mx_in, in);
    
            int delta = min(lp, rp);
            int qlp = lp, qrp = rp;
    
            int to = in + 2 * delta;
            for (int i = in + 1; i <= to; i += 2) {
                ans[i] = min(ans[i], (i - in + 1) / 2);
                ans[i + 1] = min(ans[i + 1], (i - in + 1) / 2);
            }
    
            qlp -= delta, qrp -= delta;
            arifm[to + 1] = min(arifm[to + 1], delta - to);
            // for (int i = to + 1; i <= n; ++i) {
            //     ans[i] = min(ans[i], delta + (i - to));
            // }
        }
    }

    int mn_arifm = inf;
    for (int i = 1; i <= n; ++i) {
        mn_arifm = min(mn_arifm, arifm[i]);
        ans[i] = min(ans[i], i + mn_arifm);
    }

    while (q--) {
        int x; cin >> x;

        if (x <= mx_in) cout << 0 << " ";
        else cout << ans[x] << " ";
    }

    return 0;
}
