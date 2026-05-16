#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using sll = __int128;

bool check(vector<int> &a, vector<int> &dt) {
    for (int i = 1; i < a.size(); i++) {
        if (a[i] != a[i - 1]) return 0;
    }
    for (int i = 1; i < a.size(); i++) {
        if (dt[i] != dt[i - 1]) return 0;
    }
    return 1;
}

void solve() {
    int T;
    cin >> T;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    array<int, 2> cnt{};
    for (int i = 0; i < n; i++) cnt[a[i] % 2]++;
    if (cnt[0] * cnt[1] > 0) {
        cout << "No";
        return;
    }
    string s;cin >> s;
    vector<int> dt(n);
    for (int j = 0; j < n; j++) {
        if (s[j] == 'L') dt[j] = -1;
        else dt[j] = 1;
    }
    if (abs(a[0] - a[1]) % 2 != 0) {
        cout << "No";
        return;
    }
    if (a[0] > a[1]) {
        swap(a[0], a[1]);
        swap(s[0], s[1]);
    }
    if (a[0] == a[1]) {
        if (s[0] == s[1]) {
            cout << "Yes\n";
            if (T >= 2) cout << m << '\n';
            if (T >= 3) cout << "0";
        } else if (a[0] >= m - a[0] + 1) {
            cout << "Yes\n";
            if (T >= 2) cout << a[0] << '\n';
            if (T >= 3) cout << "0";
            return;
        } else {
            cout << "Yes\n";
            if (T >= 2) cout << m - a[0] + 1 << '\n';
            if (T >= 3) cout << "1\n" << m << ' ' << a[0];
        }
        return;
    }
    int add = 0;
    if (s[0] == 'L' && s[1] == 'R') {
        int tmp = max(a[0] - 1, m - a[1]);
        a[0] = tmp - a[0] + 1;
        a[1] = m - (tmp - (m - a[1]));
        s[0] = 'R';
        s[1] = 'L';
        add += tmp;
    }
    if (s[0] == 'L' && s[1] == 'L') {
        int tmp = a[0] - 1;
        a[0] = 1;
        a[1] -= tmp;
        s[0] = 'R';
        add += tmp;
    }
    if (s[0] == 'R' && s[1] == 'R') {
        int tmp = m - a[1];
        a[0] += tmp;
        a[1] = m;
        s[1] = 'L';
        add += tmp;
    }
    if (s[0] == 'R' && s[1] == 'L') {
        int pos = (a[0] + a[1]) / 2;
        int tm = (a[1] - a[0]) / 2 + add;
        if (pos < m - pos + 1) {
            pos = m - pos + 1;
            tm += m;
        }
        cout << "Yes\n";
        if (T >= 2) {
            cout << pos << '\n';
        }
        if (T >= 3) {
            cout << 1 << '\n' << tm << ' ' << pos;
        }
        return;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdin);
#endif
    int test = 1;
    // cin >> test;
    while (test--) {
        solve();
    }
}
