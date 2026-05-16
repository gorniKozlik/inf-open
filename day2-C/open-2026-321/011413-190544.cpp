#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define endl '\n'
#define int long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

const int mod = 998244353;

int add(int a, int b) {
    if (a + b >= mod) {
        return a + b - mod;
    } else {
        return a + b;
    }
}

int sub(int a, int b) {
    if (a < b) {
        return a - b + mod;
    } else {
        return a - b;
    }
}

int mul(int a, int b) {
    return 1ll * a * b % mod;
}

int binpow(int a, int b) {
    int ans = 1;
    while (b > 0) {
        if (b % 2) {
            ans = mul(ans, a);
        }
        a = mul(a, a);
        b /= 2;
    }
    return ans;
}

const int inf = 1e18;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ev.emplace_back(l, 0);
        ev.emplace_back(r, 1);
    }
    map<int, int> cnt, L, R;
    sort(all(ev));
    int opened = 0, closed = 0;
    for (auto [x, tp] : ev) {
        L[x] = closed;
        cnt[x] = opened;
        if (tp == 0) {
            opened++;
            cnt[x]++;
        } else {
            opened--;
            closed++;
        }
        R[x] = n - opened - closed;
    }
    // vector<int> val(n + 1, inf);
    int best = inf;
    for (auto [pos, x] : cnt) {
        int add = min(L[pos], R[pos]);
        best = min(best, -x + -add);
        // for (int i = 0; i <= x; i++) {
        //     val[i] = 0;
        // }
        // for (int i = 0; i <= add; i++) {
        //     val[x + 2 * i] = min(val[x + 2 * i], i);
        //     val[x + 2 * i - 1] = min(val[x + 2 * i - 1], i);
        // }
        // for (int i = x + 2 * add; i <= n; i++) {
        //     val[i] = min(val[i], i - x - add);
        // }
    }
    vector<int> val(n + 1, -inf);
    for (auto [pos, x] : cnt) {
        int it = x + 2 * min(L[pos], R[pos]);
        assert(it <= n);
        val[it] = max(val[it], x);
    }
    vector<int> pref(n + 2, -inf);
    for (int i = n; i >= 0; i--) {
        pref[i] = max(pref[i + 1], val[i]);
    }
    while (q--) {
        int k;
        cin >> k;
        int now = pref[k];
        if (pref[k] == -inf) {
            cout << k + best << " ";
        } else {
            cout << max(0ll, (k - now + 1) / 2) << " ";
        }
    }
    // while (q--) {
    //     int k;
    //     cin >> k;
    //     if (val[k] == inf) {
    //         cout << k + best << " ";
    //     } else {
    //         cout << val[k] << " ";
    //     }
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("C:/work/test/input.txt", "r", stdin);
    solve();
    return 0;
}