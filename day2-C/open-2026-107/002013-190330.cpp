#ifdef ONPC
    #define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

#define all(v) begin(v), end(v)

using ll = long long;

struct segment_tree {
    struct node {
        ll pref = 0, sum = 0;
        node() {};
        node(ll x) : pref(max(0LL, x)), sum(x) {};
    };

    node merge(node a, node b) {
        node c;
        c.pref = max(a.pref, a.sum + b.pref);
        c.sum = a.sum + b.sum;
        return c;
    }

    int n;
    vector<node> t;
    segment_tree(const vector<ll> &a) : n(a.size()), t(2 * n) {
        for (int i = 0; i < n; ++i) {
            t[i + n] = node(a[i]);
        }
        for (int v = n - 1; v > 0; --v) {
            t[v] = merge(t[v << 1], t[v << 1 | 1]);
        }
    }
    void upd(int k, ll x) {
        if (k >= n) return;
        int v = k + n;
        t[v] = node(x);
        while (v >>= 1) {
            t[v] = merge(t[v << 1], t[v << 1 | 1]);
        }
    }
    node get(int l, int r) {
        r++;
        l = max(l, 0), r = min(r, n);
        l += n, r += n;
        node left = {}, right = {};
        while (l < r) {
            if (l & 1) left = merge(left, t[l++]);
            if (r & 1) right = merge(t[--r], right);
            l >>= 1, r >>= 1;
        }
        return merge(left, right);
    }
};

void test_case() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> coords;
    for (auto &[l, r] : a) {
        cin >> l >> r;
        coords.push_back(l);
        coords.push_back(r);
    }

    sort(all(coords));
    coords.erase(unique(all(coords)), coords.end());
    int k = coords.size();
    auto compress = [&](int x) {
        return lower_bound(all(coords), x) - coords.begin();
    };

    for (auto &[l, r] : a) {
        l = compress(l);
        r = compress(r);
    }

//    auto scanline = [&]() {
//        vector<pair<int, int>> e;
//        for (auto [l, r] : a) {
//            e.push_back({l, -1});
//            e.push_back({r, +1});
//        }
//
//        sort(all(e));
//        int cur = 0, ans = -1, l = -1, r = -1, prev = 0;
//        for (auto [x, tp] : e) {
//            if (tp == -1) {
//                cur++;
//                if (ans < cur) {
//                    l = x;
//                    prev = 1;
//                } else {
//                    prev = 0;
//                }
//            } else {
//                cur--;
//                if (prev) {
//                    r = x;
//                    prev = 0;
//                }
//            }
//        }
//
//        return ans;
//    };

//    int cur = scanline();
    vector<ll> b(k + 1);
    for (auto [l, r] : a) {
        b[l]++;
        b[r + 1]--;
    }
    segment_tree st(b);
    int cur = st.get(0, k).pref;
//    cout << cur << ' ' << st.get(0, 4).pref << '\n';
//    for (auto i : b) {
//        cerr << i << ' ';
//    }
//    return;
    vector<int> ans(n + 1);

    set<pair<int, int>> sl, sr;
    for (int i = 0; i < n; ++i) {
        auto [l, r] = a[i];
        sl.insert({l, i});
        sr.insert({r, i});
    }

    int last = cur + 1;
    while (cur < n) {
        auto [mxl, i] = *sl.rbegin();
        auto [mnr, j] = *sr.begin();
        if (i == j) break;
        sl.erase({mxl, i});
        sr.erase({mnr, j});

        for (auto idx : {i, j}) {
            auto [l, r] = a[idx];
            b[l]--;
            b[r + 1]++;
            st.upd(l, b[l]);
            st.upd(r + 1, b[r + 1]);
        }

        swap(a[i].first, a[j].second);

        for (auto idx : {i, j}) {
            auto [l, r] = a[idx];
            b[l]++;
            b[r + 1]--;
            st.upd(l, b[l]);
            st.upd(r + 1, b[r + 1]);
            sl.insert({l, idx});
            sr.insert({r, idx});
        }

        cur = st.get(0, k).pref;
//        cerr << format("{} {}\n", cur, st.get(0, 3).pref);
        ans[last]++;
        last = cur + 1;
    }

    for (int i = 1; i <= n; ++i) {
        ans[i] += ans[i - 1];
//        cerr << ans[i] << ' ';
    }
//    cerr << '\n';

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
//    cin >> t;
    while (t--) {
        test_case();
    }

    return 0;
}
