#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;
using ll = long long;

template<typename T>
ll szof(const T &a) {
    return a.size();
}

template<typename T>
using ordered_set = tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;

template<typename T, typename Y>
istream &operator>>(istream &in, pair<T, Y> &a) {
    return in >> a.first >> a.second;
}

template<typename T, typename Y>
ostream &operator<<(ostream &out, const pair<T, Y> &a) {
    return out << a.first << ' ' << a.second;
}

template<typename T>
istream &operator>>(istream &in, vector<T> &a) {
    for (auto &i : a) {
        in >> i;
    }
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
    for (const auto &i : a) {
        out << i << ' ';
    }
    return out;
}

template<typename T>
void print(const vector<T> &a, string c = "\n") {
    for (const auto &i : a) {
        cout << i << c;
    }
}

// bool cmp(ll a, ll b) {
//     return a > b;
// }

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x;
    // map<ll, vector<ll>> start_in, ends_in;
    map<ll, ll> cnt_start, cnt_end;
    for (int i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        x.emplace_back(l);
        x.emplace_back(r);
        cnt_start[l]++;
        cnt_end[r]++;
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());
    ll left = 0, right = n, open = 0;
    vector<ll> mn(n + 1, n + 1), cc2(n + 1), cc1(n + 1);
    ll id = 0, mx = 0;
    vector<vector<pair<ll, ll>>> st2(n + 1), st1(n + 1);
    vector<vector<ll>> e20(n + 1), e21(n + 1), e1(n + 1);
    for (auto xi : x) {
        // ll c_start = szof(start_in[xi]);
        ll cs = cnt_start[xi], ce = cnt_end[xi];
        right -= cs;
        open += cs;

        ll c2 = min(left, right), c1 = min(left - c2, cs) + min(right - c2, ce);
        // cc2[id] = c2;
        // cc1[id] = c1;
        // ++id;
        mx = max(mx, open);

        left += ce;
        open -= ce;
        if (c2) {
            st2[open].emplace_back(0ll, c2);
        }
        if (c1) {
            st1[open + c2 * 2].emplace_back(c2, c1);
        }
    }
    vector<ll> ans(n + 1, 1e18);
    multiset<ll> s20, s21, s1;
    ll p20 = 0, p21 = 0, p1 = 0;
    for (int i = 0; i <= n; ++i) {
        (i % 2 == 1 ? p20 : p21)++;
        p1++;
        for (auto [x0, y0] : st2[i]) {
            auto &s = i % 2 == 0 ? s20 : s21;
            auto &e = i % 2 == 0 ? e20 : e21;
            auto &p = (i % 2 == 0 ? p20 : p21);
            s.insert(x0 - p);
            e[i + y0 * 2].emplace_back(x0 - p);
        }
        for (auto [x0, y0] : st1[i]) {
            s1.insert(x0 - p1);
            e1[i + y0].emplace_back(x0 - p1);
        }

        if (!s20.empty()) {
            ans[i] = min(ans[i], *s20.begin() + p20);
        }
        if (!s21.empty()) {
            ans[i] = min(ans[i], *s21.begin() + p21);
        }
        if (!s1.empty()) {
            ans[i] = min(ans[i], *s1.begin() + p1);
        }

        for (auto x0 : e20[i]) {
            s20.erase(s20.find(x0));
        }
        for (auto x0 : e21[i]) {
            s21.erase(s21.find(x0));
        }
        for (auto x0 : e1[i]) {
            s1.erase(s1.find(x0));
        }
    }
    for (int i = 0; i < q; ++i) {
        ll k;
        cin >> k;
        if (k <= mx) {
            cout << "0 ";
        } else {
            cout << ans[k] << ' ';
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int times = 1;
    // cin >> times;
    while (times--) {
        solve();
        cout << '\n';
    }
}
