#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define int long long
// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2")

using namespace __gnu_pbds;
using ll = long long;
using namespace std;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve1() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i != 0 && a[i] % 2 != a[i - 1] % 2) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int get(int x, char c, int t, int m) {
    if (c == 'L') {
        x -= t;
    } else {
        x += t;
    }
    x = (x % (2 * m - 2) + 2 * m - 2) % (2 * m - 2);
    if (x < m) {
        return x;
    }
    return 2 * m - 2 - x;
}

void solve2() {
    int n, m, ans;
    cin >> n >> m;
    // cout << get(x, 'R', y, m) << "\n";
    ans = m;
    string s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        if (i != 0 && a[i] % 2 != a[i - 1] % 2) {
            cout << "No\n";
            return;
        }
    }
    sort(a.begin(), a.end());
    cin >> s;
    // if (n == 3 && m == 4 && s[0] == 'R' && s[1] == 'R' && s[2] == 'L' && a[0] == 0 && a[1] == 2 && a[2] == 2) {
    //     return;
    // }
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int mx = -1;
            // cout << i << " " << j << '\n';
            for (int t = 0; t < 2 * m + 10 ; t++) {
                if (get(a[i], s[i], t, m) == get(a[j], s[j], t, m)) {
                    mx = max(mx, get(a[i], s[i], t, m));
                }
            }
            // cout << mx << "\n";
            ans = min(ans, mx);
        }
    }
    cout << ans + 1 << "\n";
}

void solve3() {
    int n, m, ans;
    cin >> n >> m;
    // ans = m;
    string s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        if (i != 0 && a[i] % 2 != a[i - 1] % 2) {
            cout << "No\n";
            return;
        }
    }
    cin >> s;
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int mx = -1, tm;
            // cout << i << " " << j << '\n';
            for (int t = 0; t <= 2 * m + 10; t++) {
                if (get(a[i], s[i], t, m) == get(a[j], s[j], t, m)) {
                    if (mx < get(a[i], s[i], t, m)) {
                        mx = get(a[i], s[i], t, m);
                        tm = t;
                    }
                }
            }
            // cout << mx << "\n";
            // ans = min(ans, mx);
            cout << mx + 1 << "\n";
            cout << 1 << "\n";
            cout << tm << " " << mx + 1 << "\n";
            return;
        }
    }
    cout << ans + 1 << "\n";
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
    cin >> t;
    if (t == 1) {
        solve1();
    } else if (t == 2) {
        solve2();
    } else {
        solve3();
    }
}
