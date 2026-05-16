#include <bits/stdc++.h>

using namespace std;

#define sll __int128_t
#define ll long long
#define ld long double
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define size(x) (int)(x).size()

const int MOD = 998244353, MAXN = 3e5 + 100, inf = 1e9;
const ll INF = 1e18;

int add(int a, int b) {
    if (a + b >= MOD) {
        return a + b - MOD;
    }
    return a + b;
}
int sub(int a, int b) {
    if (a - b < 0) {
        return a - b + MOD;
    }
    return a - b;
}
int mult(int a, int b) {
    return ((ll)a * b) % MOD;
}
int kv(int a) {
    return ((ll)a * a) % MOD;
}
int fast_pow(int x, int a) {
    if (a == 0) return 1;
    if (a == 1) return x;
    if (a & 1) return mult(x, fast_pow(x, a - 1));
    return kv(fast_pow(x, a / 2));
}


void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> cord;
    vector<pair<int, int>> scan;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        cord.push_back(l);
        cord.push_back(r);
        scan.push_back({l, 1});
        scan.push_back({r, -1});
    }
    sort(all(scan));
    sort(all(cord));
    cord.resize(unique(all(cord)) - cord.begin());
    vector<int> pref(2 * n + 1), suf(2 * n + 1);
    int cnt = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        auto [x, ev] = scan[i];
        if (ev == -1) cnt++;
        pref[i] = cnt;
    }
    cnt = 0;
    for (int i = 2 * n - 1; i > 0; i--) {
        auto [x, ev] = scan[i];
        if (ev == 1) cnt++;
        suf[i - 1] = cnt;
    }
    vector<int> mn(n + 1, inf), mx(n + 1, -inf);
    for (int i = 0; i < 2 * n - 1; i++) {
        // cout << pref[i] << " " << suf[i] << " ";
        int a = n - suf[i] - pref[i];
        int b = 2 * min(suf[i], pref[i]);
        // cout << a << " " << b << endl;
        mn[a] = 0;
        mx[a + b] = max(mx[a + b], a - 1);
    }
    for (int i = n - 1; i > -1; i--) {
        mx[i] = max(mx[i + 1], mx[i]);
        mn[i] = min(mn[i + 1], mn[i]);
    }
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        if (mn[x] == 0) {
            cout << "0 ";
        }
        else {
            cout << (x - mx[i]) / 2 << " ";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int ttt = 1;
    //cin >> ttt;
    while (ttt--) {
        solve();
    }
}