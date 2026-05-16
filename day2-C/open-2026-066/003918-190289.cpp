#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

#define int long long
#define all(x) x.begin(), x.end()

const int inf = 1e18;
const int mod = 998244353;

template<typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

struct segTree {
    vector<int> t;
    int n;

    segTree(int x) {
        n = x;
        t.assign(2 * n, inf);
        // for (int i = 0; i < n; i++) t[i + n] = a[i];
        // for (int i = n - 1; i >= 0; i--) t[i] = max(t[i << 1], t[(i << 1) | 1]);
    }

    int get(int l, int r) {
        int ans = -inf;
        l += n, r += n;
        while (l < r) {
            if (l & 1) ans = max(ans, t[l++]);
            if (r & 1) ans = max(ans, t[--r]);
            l >>= 1, r >>= 1;
        }
        return ans;
    }

    void upd(int i, int x) {
        i += n, t[i] = x, i >>= 1;
        while (i) t[i] = max(t[i << 1], t[(i << 1) | 1]), i >>= 1;
    }
};

struct Fen {
    vector<int> t;
    int n;

    Fen(int x) {n = x;t.assign(n + 1, 0);}
    int sum(int r) {int ans = 0;for (; r > 0; r -= r & -r) ans += t[r];return ans;}
    int get(int l, int r) {return sum(r) - sum(l - 1);}
    void upd(int i, int x) {for (; i <= n; i += i & -i) t[i] += x;}
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> a(n);
    for (auto& i : a) cin >> i.first >> i.second;
    vector<int> c;
    for (auto& [u, v] : a) c.push_back(u), c.push_back(v);
    sort(all(c));
    c.resize(unique(all(c)) - c.begin());
    for (auto& [u, v] : a) {
        u = lower_bound(all(c), u) - c.begin();
        v = lower_bound(all(c), v) - c.begin();
    }

    int sz = c.size();
    set<int> idx;
    vector<vector<int>> que1(sz);
    vector<vector<int>> que2(sz);
    for (int i = 0; i < n; i++) {
        auto [l, r] = a[i];
        que1[l].push_back(i);
        que2[r].push_back(i);
    }

    vector<int> ans(n + 1, inf);
    set<int> st;
    int sz3 = c.size();
    int cnt1 = 0, cnt2 = n;
    int mx = 0;
    for (int i = 0; i < sz3; i++) {
        for (auto& j : que1[i]) st.insert(j), cnt2--;
        if (1) {
            mx = max(mx, (int)(st.size()));

    int sz1 = cnt1;
    int sz2 = cnt2;
    sz = min(sz1, sz2);

    int prime = st.size() + 1;
    int op = 0;
    for (int j = 0; j < sz; j++) {
        sz1--, sz2--;
        ans[prime] = min(ans[prime], ++op);
        prime++;
        ans[prime] = min(ans[prime], op);
        prime++;
    }

    sz = sz1 + sz2;
    for (int j = 0; j < sz; j++) {
        ans[prime] = min(ans[prime], ++op);
        prime++;
    }
        }
        for (auto& j : que2[i]) st.erase(j), cnt1++;
    }

    for (int i = 1; i <= mx; i++) ans[i] = 0;
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif

    int t = 1;
    // cin >> t;

    while (t--) solve();
}