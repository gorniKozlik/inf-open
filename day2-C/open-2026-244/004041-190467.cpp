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
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        b.push_back({a[i].first, -1});
        b.push_back({a[i].second, 1});
    }
    sort(all(b));
    int cnt = 0;
    int mx = 0, l = 0, r = 0;
    for (int i = 0; i < 2 * n; i++) {
        cnt -= b[i].second;
        if (cnt > mx) {
            mx = cnt;
            l = b[i].first;
            r = b[i + 1].first;
        }
    }
    int cnt_left = 0, cnt_right = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (b[i].second == 1 && b[i].first < l) {
            cnt_left++;
        }
        if (b[i].second == -1 && b[i].first > r) {
            cnt_right++;
        }
    }
    vector<int> answer(n + 10, 0);
    int cur = mx;
    int val = 0;
    while (cur <= n) {
        if (cnt_left > 0 && cnt_right > 0) {
            val++;
            answer[cur + 1] = val;
            answer[cur + 2] = val;
            cur += 2;
            cnt_left--; cnt_right--;
        } else {
            val++;
            answer[cur + 1] = val;
            cur++;
        }
    }
    while (q--) {
        int k; cin >> k;
        cout << answer[k] << " ";
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