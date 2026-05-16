#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()
#define revall(a) a.rbegin(), a.rend()

#pragma GCC optimize("03")

const int mod = 998244353;

int fastpow(int base, int power, int modx) {
    if (power == 0) {
        return 1;
    }
    if (power % 2 == 0) {
        int x = fastpow(base, power / 2, modx) % modx;
        return (x * x) % modx;
    } else {
        return (base * fastpow(base, power - 1, modx)) % modx;
    }
}

void solve() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> a(n), b;
    vector<int> x1, x2;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        x2.push_back(a[i].first);
        x1.push_back(a[i].second);
        b.push_back({a[i].first, -1});
        b.push_back({a[i].second, 1});
    }
    vector<int> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i];
    }
    vector<int> answer(q, 1e9);
    sort(all(b));
    int cnt_left = 0, cnt_right = 0;
    sort(all(x1));
    sort(all(x2));
    int cnt = 0;
    int sigma = 0;
    int pos = 0;
    int mx = 0;
    for (int i = 0; i < 2 * n; i++) {
        cnt -= b[i].second;
        mx = max(mx, cnt);
        cnt_left = lower_bound(all(x1), b[i].first) - x1.begin();
        if (i == 2 * n - 1) {
            cnt_right = 0;
        } else {
            cnt_right = n - (upper_bound(all(x2), b[i + 1].first) - x2.begin());
        }
        if (cnt + min(cnt_left, cnt_right) > sigma) {
            sigma = cnt + min(cnt_left, cnt_right);
            pos = i;
        }
    }
    // cout << pos << "\n";
    cnt_left = lower_bound(all(x1), b[pos].first) - x1.begin();
    if (pos == 2 * n - 1) {
        cnt_right = 0;
    } else {
        cnt_right = n - (upper_bound(all(x2), b[pos + 1].first) - x2.begin());
    }
    // cout << sigma << " " << cnt_left << " " << cnt_right << "\n";
    for (int j = 0; j < q; j++) {
        int f = min(cnt_left, cnt_right);
        cnt = sigma - f;
        int k = queries[j];
        if (k <= mx) {
            answer[j] = 0;
        }
        k -= cnt;
        if (k <= 0) {
            answer[j] = 0;
        } else {
            if (k <= 2 * f) {
                answer[j] = min(answer[j], (k + 1) / 2);
            } else {
                int lol = f;
                k -= 2 * f;
                answer[j] = min(answer[j], lol + k);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << answer[i] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
    }
}