#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct st {
    int l, r;
};

bool cmp(st a, st b) {
    return a.l < b.l;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<st> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
    }
    sort(a.begin(), a.end(), cmp);
    int l = 0, r = n - 1;
    int cnt = 0;
    while (l < r) {
        if (a[l].r < a[r].l) {
            cnt++;
            l++, r--;
        } else {
            l++;
        }
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << cnt;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
        cout << '\n';
    }
    return 0;
}