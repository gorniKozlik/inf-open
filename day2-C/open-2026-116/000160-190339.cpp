#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    vector<int> ans(n + 1, (int) 1e18);
    vector<int> x;
    for (int i = 0; i < n; i++) x.emplace_back(a[i].first), x.emplace_back(a[i].second);
    sort(x.begin(), x.end());
    for (int i: x) {
        int c1 = 0, c2 = 0, inter = 0;
        for (int j = 0; j < n; j++) {
            if (a[j].second < i) c1++;
            else if (a[j].first > i) c2++;
            else inter++;
        }
        ans[inter] = 0;
        for (int j = inter + 2; j <= inter + min(c1, c2) * 2; j += 2)
            ans[j] = min(ans[j], (j - inter) / 2);
    }
    ans[n] = min(ans[n], n / 2);
    for (int i = n - 1; i >= 0; i--)
        ans[i] = min(ans[i], ans[i + 1]);
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    return 0;
}
