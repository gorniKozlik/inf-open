#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int inf = 1e9 + 7;
const ll infll = 1e18;

template<typename T>
istream &operator>>(istream &is, vector<T> &a) {
    for (auto &i : a) {
        is >> i;
    }
    return is;
}

int32_t main() {
#ifdef LOCAL
    freopen("C:\\work\\input.txt", "r", stdin);
#else
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> seg(n);
    for (auto &[l, r] : seg) {
        cin >> l >> r;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << k - 1 << "\n";
    }
    return 0;
}
