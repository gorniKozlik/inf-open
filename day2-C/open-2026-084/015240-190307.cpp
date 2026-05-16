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

struct Fenwick {
    int n;
    vector<int> t;

    Fenwick(int _n) : n(_n) {
        t.resize(n + 1);
    }

    int get(int i) {
        int ans = 0;
        for (; i > 0; i -= i & (-i)) {
            ans += t[i];
        }
        return ans;
    }

    int get(int l, int r) {
        return get(r) - get(l);
    }

    void add(int i, int d) {
        for (++i; i <= n; i += i & (-i)) {
            t[i] += d;
        }
    }
};

int32_t main() {
#ifdef LOCAL
    freopen("C:\\work\\input.txt", "r", stdin);
#else
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> b;
    for (auto &[l, r] : a) {
        cin >> l >> r;
        b.push_back(l);
        b.push_back(r);
    }
    vector<int> qs(q);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        qs[i] = k;
    }
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());
    for (auto &[l, r] : a) {
        l = lower_bound(b.begin(), b.end(), l) - b.begin();
        r = lower_bound(b.begin(), b.end(), r) - b.begin();
    }
    set<pair<int, int>> stl, str;
    for (auto [l, r] : a) {
        stl.insert({l, r});
        str.insert({r, l});
    }
    int cur = 0;
    set<pair<int, int>> st;
    while (true) {
        Fenwick tr(b.size());
        int mx = 0;
        for (auto [l, r] : stl) {
            tr.add(r, 1);
            mx = max(mx, tr.get(l, b.size()));
        }
        st.insert({mx, cur});
        auto [l1, r1] = *prev(stl.end());
        auto [r2, l2] = *str.begin();
        if (l1 <= r2) {
            break;
        }
        stl.erase({l1, r1});
        stl.erase({l2, r2});
        str.erase({r1, l1});
        str.erase({r2, l2});
        stl.insert({l2, r1});
        str.insert({r1, l2});
        stl.insert({r2, l1});
        str.insert({l1, r2});
        ++cur;
    }
    for (auto i : qs) {
        auto it = st.lower_bound(pair{i, -inf});
        assert(it != st.end());
        cout << it->second << " ";
    }
    cout << "\n";
    return 0;
}
