#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--) solve();
}

#define int ll

int mod = 998244353, inf = 1e9+100;
ll infll = 1e18+100;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<array<int, 2>> a(n);
    vector<int> L(n), R(n);
    int p = 0;
    for (auto& [l, r] : a) {
        cin >> l >> r;
        L[p] = l;
        R[p] = r;
        ++p;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << (k + 1) / 3 << ' ';
    }
    cout << '\n';
}