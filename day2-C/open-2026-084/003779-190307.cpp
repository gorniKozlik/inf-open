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
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> stl, str;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        stl.insert({l, r});
        str.insert({r, l});
    }
    while (q--) {
        int k;
        cin >> k;
        assert(k == n);
        set<pair<int, int>> curl = stl, curr = str;
        int cnt = 0;
        while (true) {
            auto [l1, r1] = *prev(curl.end());
            auto [r2, l2] = *curr.begin();
            if (l1 <= r2) {
                break;
            }
            curl.erase(prev(curl.end()));
            curr.erase(curr.begin());
            curl.insert({l2, r1});
            curr.insert({r1, l2});
            curl.insert({r2, l1});
            curr.insert({l1, r2});
            ++cnt;
        }
        cout << cnt << " ";
    }
    cout << "\n";
    return 0;
}
