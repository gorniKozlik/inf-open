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
    int x, tp;
};

bool cmp(node a, node b) {
    return a.x < b.x;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > otr(n);
    vector<node> all;
    for (int i = 0; i < n; i++) {
        cin >> otr[i].first >> otr[i].second;
        all.push_back({otr[i].first, 1});
        all.push_back({otr[i].second, 2});
    }
    sort(all.begin(), all.end(), cmp);
    vector<int> ans(n + 1, INF), mx(n + 1, 0);
    int sm = 0, cnt1 = 0, cnt2 = n;
    for (auto [x, tp]: all) {
        if (tp == 1) {
            sm++;
            cnt2--;
        } else {
            sm--;
            cnt1++;
        }
        ans[sm] = 0;
        mx[sm] = max(mx[sm], min(cnt1, cnt2));
    }
    ans[0] = 0;

    for (int i = 0; i <= n; i++) {
        if (mx[i] != 0 && i + 2 <= n) {
            ans[i + 2] = min(ans[i + 2], ans[i] + 1);
            mx[i + 2] = max(mx[i + 2], mx[i] - 1);
        }
        if (i + 1 <= n) {
            ans[i + 1] = min(ans[i + 1], ans[i] + 1);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }


    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}
