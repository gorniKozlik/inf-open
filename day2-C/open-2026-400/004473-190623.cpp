#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 998'244'353;

ostream& operator<<(ostream& out, vector<int> v) {
    for (auto el : v) {
        out << el << " ";
    }
    return out << "\n";
}
ostream& operator<<(ostream& out, deque<int> v) {
    for (auto el : v) {
        out << el << " ";
    }
    return out << "\n";
}
istream& operator>>(istream& in, vector<int>& v) {
    for (auto& el : v) {
        in >> el;
    }
    return in;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    map<int, int> mp;
    for (auto& [x, y] : a) {
        cin >> x >> y;
        mp[x] = 0;
        mp[y] = 0;
    }
    int c = 0;
    for (auto& [key, val] : mp) {
        val = c++;
    }
    vector<int> v(n * 2);
    for (auto& [x, y] : a) {
        x = mp[x];
        y = mp[y];
        v[x] = y;
        v[y] = x;
    }
//    cout << v << "\n";
    vector<int> ans(n + 1, 1e9);
    ans[0] = ans[1] = 0;
    int cnt = 0;
    for (int i = 0; i < n * 2; i++) {
        if (i < v[i]) cnt++;
        else cnt--;
        int l = i + 1 - cnt;
        int r = n * 2 - cnt * 2 - l;
//        cout << cnt << " " << l << "_" << r << "\n";
        l = min(l, r);
        for (int j = 0; j * 2 <= l; j++) {
            ans[cnt + j * 2] = min(ans[cnt + j * 2], j);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
//    cout << ans;
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
