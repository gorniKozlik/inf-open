#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

int inf = (int)1000 * 1000 * 1000 * 1000 * 1000 * 1000 + 100;
// int inf = (int)1000 * 1000 * 1000 + 100;

/*
#pragma optimize("O3")
#pragma optimize("avx,avx2,bmi,bmi2")
*/

mt19937_64 rnd(228);

void print(vector <int> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << '\n';
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector <int> l(n);
    vector <int> r(n);
    for (int i = 0; i < n; i ++) {
        cin >> l[i] >> r[i];
    }

    vector <pair <int, int>> t;
    for (int i = 0; i < n; i ++) {
        t.push_back({l[i], 1});
        t.push_back({r[i], -1});
    }

    sort(t.begin(), t.end());

    vector <int> ans(n + 1, inf);
    int cnt = 0;
    for (int i = 0; i < t.size(); i ++) {
        cnt += t[i].second;
        int a = ((i + 1) - cnt) / 2;
        int b = ((t.size() - i - 1) - cnt) / 2;
        for (int j = 0; j <= cnt; j ++) {
            ans[j] = 0;
        }

        for (int j = cnt + 1; j <= cnt + min(a, b) * 2; j ++) {
            ans[j] = min(ans[j], (j - cnt + 1) / 2);
        }
        for (int j = cnt + min(a, b) * 2 + 1; j <= n; j ++) {
            ans[j] = min(ans[j], min(a, b) + (j - cnt - min(a, b) * 2));
        }
    }

    while (q --) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif

    int _ = 1;
    // cin >> _;
    while (_ --) {
        solve();
    }
}