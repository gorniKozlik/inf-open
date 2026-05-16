#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()

const ll MOD = 998244353;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> coords(n);
    for (auto & el : coords) {
        cin >> el.first >> el.second;
    }
    vector<ll> ans(n + 1);
    for (int i = 0; i < n / 2; ++i) {
        ans[2 * i + 1] = i + 1;
        ans[2 * i + 2] = i + 1;
    }
    if (n % 2 == 1) {
        ans.back() = (n) / 2;
    }
    ans[0] = 0;
    for (int op = 0; op < q; ++op) {
        ll x;
        cin >> x;
        cout << ans[x - 1] << '\n';
    }
}