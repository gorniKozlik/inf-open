#include <bits/stdc++.h>

#define int long long
using ll = long long;
using ld = long double;
using namespace std;

const int INF = 1e18, MAXN = 1e5, mod = 998244353;

void solve();

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
        cout << "\n";
    }
}

struct node {
    int l, r;
};

bool cmp(node a, node b) {
    return a.l < b.l;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<node> all(n);
    for (int i = 0; i < n; i++) {
        cin >> all[i].l >> all[i].r;
    }
    sort(all.begin(), all.end(), cmp);
    vector<int> ans(n + 1, INF);
    for (int l = 0; l < n; l++) {
        int r = l, mn_r = all[l].r;
        while (r != n - 1) {
            if (all[r + 1].l > mn_r) {
                break;
            }
            mn_r = min(mn_r, all[r + 1].r);
            r++;
        }
        int sm = r - l + 1, ans_cnt = 0;
        ans[sm] = ans_cnt;
        int l1 = l, r1 = r;
        while (l1 != 0 || r1 != n - 1) {
            if (l1 > 0 && r1 < n - 1) {
                sm += 2;
                ans_cnt++;
                l1--;
                r1++;
                ans[sm] = min(ans[sm], ans_cnt);
                continue;
            }
            if (l1 > 0) {
                sm++;
                l1--;
                ans_cnt++;

                ans[sm] = min(ans[sm], ans_cnt);
                continue;
            }

            sm ++;
            r1++;
            ans_cnt++;

            ans[sm] = min(ans[sm], ans_cnt);
        }
    }

    for (int i = (int) ans.size() - 2; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }


    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}
