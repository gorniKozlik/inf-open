#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <immintrin.h>

using namespace std;
using namespace __gnu_pbds;

// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2,bmi,popcnt")
// #pragma GCC auto_inline("binpow")


// #define double long double
#define int int_fast64_t
#define endl "\n"
#define ordered_set  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

constexpr int MOD = 998244353;
constexpr int INF = 2e18;
constexpr int K = 3;
constexpr int P = 31;
constexpr double eps = 1e-9;
constexpr int MAXN = 30;
constexpr int MOD1 = (1ll << 61) - 1;

inline int pls(int a, int b) {
    if (a + b >= MOD1) return a + b - MOD1;
    return a + b;
}

inline int mns(int a, int b) {
    return pls(a, MOD1 - b);
}

inline int umn(int a, int b) {
    __int128 c = __int128(a) * b;
    return pls(c & MOD1, c >> 61);
}

int binpow(int n, int k, int mod) {
    if (!k) return 1;
    if (k & 1) return n * binpow(n, k ^ 1, mod) % mod;
    int c = binpow(n, k >> 1, mod);

    return c * c % mod;
}


// struct resh {
//     bool r[MAXN];
//
//     constexpr resh() {
//         for (int i = 0; i < MAXN; i++) {
//             r[i] = true;
//         }
//         r[1] = false;
//         for (int i = 2; i < MAXN; i++) {
//             if (!r[i]) continue;
//             for (int j = i * i; j < MAXN; j += i) {
//                 r[j] = false;
//             }
//         }
//     }
// };



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n * 2);
    vector<int> al(2 * n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a[i * 2] = {l, 1};
        a[i * 2 + 1] = {r + 1, -1};
        al[i * 2] = l;
        al[i * 2 + 1] = r;
    }
    sort(a.begin(), a.end());
    sort(al.begin(), al.end());
    vector<int> ans(n + 1, -INF);
    vector<int> lt(2 * n), rt(2 * n);
    int cnt = 0;
    int l = 0;
    for (int i = 0; i < 2 * n; i++) {
        while (l < 2 * n && a[l].first <= al[i]) {
            if (a[l].second == -1) cnt++;
            l++;
        }
        lt[i] = cnt;
    }
    for (int i = 0; i < 2 * n; i++) {
        a[i].first--;
        a[i].second *= -1;
    }
    cnt = 0;
    l = 2 * n - 1;
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (l >= 0 && a[l].first >= al[i]) {
            if (a[l].second == -1) cnt++;
            l--;
        }
        rt[i] = cnt;
    }
    vector<pair<int, int>> otr;
    int mx = 0;
    for (int i = 0; i < 2 * n; i++) {
        otr.push_back({n - rt[i] - lt[i], n - rt[i] - lt[i] + 2 * min(rt[i], lt[i]) + 1});
        otr.push_back({ n - rt[i] - lt[i] + 2 * min(rt[i], lt[i]) + 1, n - rt[i] - lt[i]});

        mx = max(mx, n - rt[i] - lt[i]);
    }


    sort(otr.begin(), otr.end());
    multiset<int> st;
    l = 0;
    for (int i = 1; i <= n; i++) {
        while (l < otr.size() && otr[l].first <= i) {
            if (otr[l].first < otr[l].second) {
                st.insert(-otr[l].first);
            } else {
                st.erase(st.find(-otr[l].second));
            }
            l++;
        }
        if (i <= mx) {
            ans[i] = 0;
        } else if (!st.empty()) {
            ans[i] = (i + *st.begin() + 1) / 2;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -INF) ans[i] = ans[i - 1] + 1;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << endl;
    }
}
