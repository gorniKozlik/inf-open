#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
using ll = long long;
using ld = long double;

const int maxn = 2e5 + 2;
const int inf = 1e9 + 1;

int l[maxn], r[maxn];

int k[maxn];

vector<pair<int, int>> v;

int ans[maxn];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i < n + 1; i++) {
        int l, r; cin >> l >> r;
        v.emplace_back(l, 0);
        v.emplace_back(r, 1);
    }
    for (int i = 1; i < q + 1; i++) {
        cin >> k[i];
    }
    fill(ans, ans + n + 1, inf);
    sort(v.begin(), v.end());
    int cnt[2] = {0, 0};
    for (auto [x, tp] : v) {
        int cnt_r = cnt[1], cnt_l = n - cnt[0];
        int cur = n - cnt_l - cnt_r;
        /*
        for (int i = 1; i < n + 1; i++) {
            if (i < cur) {
                ans[i] = 0;
                continue;
            } else if (i <= cur + 2 * min(cnt_l, cnt_r)) {
                ans[i] = min(ans[i], (i - cur + 1) / 2);
            }
        }
        */
        for (int j = 1; j < q + 1; j++) {
            int i = k[j];
            if (i < cur) {
                ans[i] = 0;
                continue;
            } else if (i <= cur + 2 * min(cnt_l, cnt_r)) {
                ans[i] = min(ans[i], (i - cur + 1) / 2);
            } else {
                break;
            }
        }
        cnt[tp]++;
    }
    for (int i = 1; i < q + 1; i++) {
        cout << ans[k[i]] << " ";
    }
}

