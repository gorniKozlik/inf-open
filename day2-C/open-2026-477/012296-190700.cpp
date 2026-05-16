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
    vector<vector<ll>> st2(n + 1);
    multiset<ll> s;
    map<ll, pair<ll, ll>> can;
    for (auto xi : x) {
        // ll c_start = szof(start_in[xi]);
        ll cs = cnt_start[xi], ce = cnt_end[xi];
        left += ce;
        right -= cs;
        open += cs;
        mx = max(mx, open);
        open -= ce;

        ll c = min(left, right);
        st2[open + c * 2].push_back(open);
        s.insert(open);

        can[xi] = {open, c};
    }
    vector<ll> ans(n + 1, n + 1);
    for (int i = 0; i <= n; ++i) {
        if (!s.empty()) {
            ans[i] = (i - *s.rbegin() + 1) / 2;
        }
        for (auto x : st2[i]) {
            s.erase(s.find(x));
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
