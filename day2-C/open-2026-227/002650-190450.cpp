#include <bits/stdc++.h>
using ll = long long;
#define int ll

using namespace std;
const int mod = 998244353;
struct Mint {
    int val;
    Mint() {
        val = 0;
    }
    Mint(int x) {
        x %= mod;
        if (x < 0) x += mod;
        val = x;
    }
};
Mint operator+=(Mint& a, Mint b) {
    a.val += b.val;
    if (a.val >= mod) a.val -= mod;
    return a;
}
Mint operator-=(Mint& a, Mint b) {
    a.val -= b.val;
    if (a.val < 0) a.val += mod;
    return a;
}
Mint operator+(Mint a, Mint b) {
    a += b;
    return a;
}
Mint operator-(Mint a, Mint b) {
    a -= b;
    return a;
}
Mint operator*=(Mint& a, Mint b) {
    a.val = 1ll * a.val * b.val % mod;
    return a;
}
Mint operator*(Mint a, Mint b) {
    a *= b;
    return a;
}
Mint binpow(Mint x, int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    if (p % 2 == 0) {
        return binpow(x * x, p / 2);
    }
    return x * binpow(x, p - 1);
}
void solve() {
    int n, q; cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    while (q --> 0) {
        int k; cin >> k;
        cout << k / 2 << "\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t --> 0) solve();
}