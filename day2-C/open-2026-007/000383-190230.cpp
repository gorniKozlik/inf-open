#include<bits/stdc++.h>
#define all(a) a.begin(),a.end()
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int q;
    cin >> q;
    int l[n + 1], r[n + 1];
    vector<int>gol, gor;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        gol.push_back(l[i]);
        gor.push_back(r[i]);
    }
    sort(all(gol));
    sort(all(gor));
    int ans[n + 1];
    fill(ans + 1, ans + n + 1, INT_MAX);
    for (int i = 1; i <= n; i++) {
        int pt = l[i];
        int cnt = 0, cntl = 0, cntr = 0;
        cntl = upper_bound(gor.begin(), gor.end(), pt) - gor.begin();
        cntr = gol.end() - lower_bound(gol.begin(), gol.end(), pt) - 1;
        // cout << cntr << ' ';
        cnt = n - cntl - cntr;
        // cout << cnt << ' ' << cntl << ' ' << cntr << endl;
        for (int t = cnt; t >= 1; t--) {
            if (ans[t] == 0) {
                break;
            } else {
                ans[t] = 0;
            }
        }
        int te = min(cntl, cntr) * 2;
        int lim = 0;
        for (int t = cnt + te; t >= 1 + cnt; t--) {
            if (ans[t] < (t - cnt + 1) / 2) {
                lim++;
                if (lim > 100) {
                    break;
                }
            }
            ans[t] = min(ans[t], (t - cnt + 1) / 2);
        }
        int pr = ans[cnt + te];
        lim = 0;
        for (int t = n; t >= cnt + te + 1; t--) {
            if (ans[t] < pr + t - cnt - te) {
                lim++;
                if (lim > 100) {
                    break;
                }
            }
            ans[t] = min(ans[t], pr + t - cnt - te);
        }
        lim = 0;
        for (int t = cnt + te - 1; t <= n; t++) {
            if (ans[t] < pr + t - cnt - te) {
                lim++;
                if (lim > 100) {
                    break;
                }
            }
            ans[t] = min(ans[t], pr + t - cnt - te);
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}