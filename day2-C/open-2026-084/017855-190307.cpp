#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int inf = 1e9 + 7;
const ll infll = 1e18;

template<typename T>
istream &operator>>(istream &is, vector<T> &a) {
    for (auto &i: a) {
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
    int t;
    cin >> t;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a;
    for (auto &i : a) {
        --i;
    }
    string s;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 != a[0] % 2) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    bool eq = true;
    for (int i = 0; i < n; ++i) {
        if (a[i] != a[0] || s[i] != s[0]) {
            eq = false;
            break;
        }
    }
    if (eq) {
        cout << m << "\n";
        return 0;
    }
    if (n == 2) {
        if (m == 3) {
            cout << 2 << "\n";
        } else {
            cout << 3 << "\n";
        }
    } else {
        if (m == 3) {
            cout << 2 << "\n";
        } else {
            cout << 3 << "\n";
        }
    }
    return 0;
}
