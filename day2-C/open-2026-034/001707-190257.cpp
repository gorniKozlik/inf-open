#include <bits/stdc++.h>

// #define int ll
#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
#ifdef LOCAL
    cout << "____NEW_____" << endl;
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<pair<int, int>> dots;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        dots.push_back({a[i].first, -(i + 1)});
        dots.push_back({a[i].second, i + 1});
    }
    sort(dots.begin(), dots.end());
    for (int i = 0; i < 2 * n; i++) {
        if (dots[i].second < 0) {
            a[-dots[i].second - 1].first = i;
        } else {
            a[dots[i].second - 1].second = i;
        }
    }
    vector<int> rasn(n * 2 + 2);
    for (int i = 0; i < n; i++) {
        rasn[a[i].first]++;
        rasn[a[i].second]--;
    }
    vector<int> cnt(n * 2);
    int balance = 0;
    for (int i = 0; i < n * 2; i++) {
        balance += rasn[i];
        cnt[i] = balance;
    }
    vector<int> mx(n);
    for (int i = n - 1; i > -1; i--) {
        mx[i] = max(cnt[i], cnt[n - 1 - i + n - 1]);
    }
    for (int i = n - 2; i > -1; i--) {
        mx[i] = max(mx[i], mx[i + 1]);
    }
    for (int _ = 0; _ < q; _++) {
        int k;
        cin >> k;
        cout << max(0, (k - mx[k - 1] + 1) / 2) << ' ';
    }
    cout << endl;
}

signed main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int qwe = 1;
#ifdef LOCAL
    cin >> qwe;
#endif
    for (int _ = 0; _ < qwe; _++) {
        solve();
    }
}