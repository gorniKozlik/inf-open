#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#else
#pragma GCC optimize("O3,Ofast")
#pragma GCC target("avx2")
#endif

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

using oset = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using hash_table = gp_hash_table<int, int>;

void solve();

int main() {
#ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    auto timer = chrono::high_resolution_clock().now().time_since_epoch().count()/1000;
    cout << "DEBUG TIMER: ";
    int ss = timer / 1000000;
    int mm = ss / 60;
    int hh = mm / 60 + 3;
    cout << hh % 24 << ':' << mm % 60 << ':' << ss % 60 << "\n";
#endif
    int tt = 1;
    cout << fixed << setprecision(15);
    // cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}

constexpr int mod = 998244353;

struct mint {
    int x = 0;
    mint() = default;
    mint(int x) : x(x) {}
    mint operator+(const mint b) const {
        return x + b.x < mod ? x + b.x : x + b.x - mod;
    }
    mint operator-(const mint b) const {
        return x - b.x < 0 ? x - b.x + mod : x - b.x;
    }
    mint operator*(const mint b) const {
        return 1ll * x * b.x % mod;
    }
    mint operator^(int n) const {
        mint ans = 1, base = x;
        while (n) {
            if (n & 1) ans = ans * base;
            base = base * base;
            n >>= 1;
        }
        return ans;
    }
    mint inv() const {
        return operator^(mod - 2);
    }
    mint operator/(const mint b) const {
        return operator*(b.inv());
    }
};

#define int ll

vector<pair<int, int>> compress(vector<pair<int, int>>& a) {
    vector<pair<int, pair<int, int>>> vals;
    vector<pair<int, int>> ans(a.size());
    for (int i = 0; i < a.size(); ++i) {
        vals.push_back({a[i].first, {i, 1}});
        vals.push_back({a[i].second, {i, 2}});
    }
    sort(vals.begin(), vals.end());
    int cnt = -1;
    for (const auto [val, ind] : vals) {
        const auto [i, fst] = ind;
        if (fst == 1) ans[i].first = ++cnt;
        else ans[i].second = ++cnt;
    }
    return ans;
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> segs;
    vector<int> cn(2 * n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        segs.emplace_back(l, r);
    }
    auto seg = compress(segs);
    oset rs, ls;
    vector<int> delta(2 * n + 1);
    for (int i = 0; i < n; ++i) {
        auto [l, r] = seg[i];
        delta[l]++;
        delta[r + 1]--;
        rs.insert(r);
        ls.insert(l);
    }
    int sum = 0;
    for (int i = 0; i < 2 * n; ++i) {
        sum += delta[i];
        cn[i] = sum;
    }
    vector<int> extras(2 * n);
    vector<pair<int, int>> gifs;
    for (int i = 0; i < n * 2; ++i) {
        int left_guys = rs.order_of_key(i);
        int right_guys = ls.size() - ls.order_of_key(i + 1);
        int common_guys = min(left_guys, right_guys);
        int rest_guys = max(left_guys, right_guys) - common_guys;
        int new_guys = common_guys * 2 + (rest_guys > 0);
        gifs.push_back({cn[i], cn[i] + new_guys});
    }
    sort(gifs.begin(), gifs.end());
    map<int, vector<int>> events;
    for (int i = 0; i < 2 * n; ++i) {
        auto [l, r] = gifs[i];
        events[l].push_back(i);
        events[r + 1].push_back(-i-1);
    }
    vector<int> ans(n + 1);
    multiset<int> st;
    for (int x = 0; x < n + 1; ++x) {
        for (int i : events[x]) {
            if (i < 0) {
                i = -i - 1;
                st.erase(st.find(gifs[i].first));
            }else {
                st.insert(gifs[i].first);
            }
        }
        if (st.empty()) {
            ans[x] = 1e9;
            continue;
        }
        int nearest = *st.rbegin();
        ans[x] = (x - nearest + 1) >> 1;
    }
    for (int x = n - 1; x >= 0; --x) {
        ans[x] = min(ans[x], ans[x + 1]);
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}



