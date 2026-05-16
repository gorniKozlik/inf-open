#include<bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    int l[n + 1], r[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    int ans[n + 1];
    fill(ans + 1, ans + n + 1, INT_MAX);
    for (int i = 1; i <= n; i++) {
        int pt = l[i];
        int cnt = 0, cntl = 0, cntr = 0;
        for (int j = 1; j <= n; j++) {
            if (l[j] <= pt && pt <= r[j]) {
                cnt++;
            } else if (r[j] < pt) {
                cntl++;
            } else if (l[j] > pt) {
                cntr++;
            }
        }
        // cout << cnt << ' ' << cntl << ' ' << cntr << endl;
        for (int t = 1; t <= cnt; t++) {
            ans[t] = min(ans[t], 0);
        }
        int te = min(cntl, cntr) * 2;
        for (int t = cnt + 1; t <= cnt + te; t++) {
            ans[t] = min(ans[t], (t - cnt + 1) / 2);
        }
        for (int t = cnt + te + 1; t <= n; t++) {
            ans[t] = min(ans[t], ans[t - 1] + 1);
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}