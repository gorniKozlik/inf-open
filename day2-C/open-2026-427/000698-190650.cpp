#include <bits/stdc++.h>

// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2")

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128_t;

istream& operator>>(istream& is, i128 &x) {
    long long a;
    is >> a;
    x = (i128) a;
    return is;
}
ostream& operator<<(ostream& os, i128 &x) {
    long long a = (long long) x;
    os << a;
    return os;
}

const ll inf = 1e18 + 1e16;
const ll inf_t = 1e9 + 7;
const ll mod = 998244353;

#define int ll

struct quest {
    int x;
    int t;

    quest() = default;
    quest(int x, int t): x(x), t(t) {}

    bool operator<(const quest &oth) const {
        return make_pair(x, -t) < make_pair(oth.x, -oth.t);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;

    int bal = 0;
    int mx_bal = 0;

    vector <quest> qs;
    for (int i = 0; i < n; ++i) {
        qs.push_back(quest(a[i].first, 1));
        qs.push_back(quest(a[i].second, -1));
    }

    sort(qs.begin(), qs.end());
    vector <int> ans(n + 1, (n + 1) / 2);
    ans[0] = 0;
    int lt = 0;
    int rt = 0;
    for (int i = 0; i < qs.size(); ++i) {
        if (qs[i].t == 1) {
            ++lt;
        } else {
            ++rt;
        }
        bal += qs[i].t;
        mx_bal = max(mx_bal, bal);

        if (qs[i].t == 1) continue;

        ++bal;
        int lft = rt - 1;
        int rht = n - lt;

        int add = 2 * min(lft, rht);
        for (int j = 1; j <= bal; ++j) {
            ans[j] = 0;
        }
        for (int j = bal + 1; j <= bal + add; ++j) {
            ans[j] = min(ans[j], (j - bal + 1) / 2);
        }
        --bal;
    }

    while (q--) {
        int k;
        cin >> k;
        cout << min(ans[k], (k + 1) / 2) << " ";
    }
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
