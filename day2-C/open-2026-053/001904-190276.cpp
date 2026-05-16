using ll = long long;
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#define all(x) (x).begin(), (x).end()
#pragma GCC optimize("O3")
struct ST {
    ll N;
    vector <ll> tree;
    ST(vector <ll> a) {
        ll n = a.size();
        N = 2 << __lg(n);
        tree.resize(2 * N, 0);
        for (ll i = 0; i < n; ++i)
            tree[i + N] = a[i];
        for (ll i = N - 1; i > 0; --i)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    void set(ll i, ll x) {
        i += N;
        tree[i] = x;
        for (i /= 2; i > 0; i /= 2) {
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
        }
    }
    ll get(ll l, ll r) {
        ll res = 0;
        for (l += N, r += N; l < r; l /= 2, r /= 2) {
            if (l & 1)
                res = max(res, tree[l++]);
            if (r & 1)
                res = max(res, tree[--r]);
        }
        return res;
    }
};
struct Query {
    ll x;
    bool opens;
    Query(ll x = 0, bool opens = 0) : x(x), opens(opens) {}
    bool operator<(Query other) {
        return x < other.x;
    }
};
int main() {
    if (1) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ll n, m;
    cin >> n >> m;
    vector <ll> xs;
    vector <pair <ll, ll>> a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        xs.push_back(a[i].first);
        xs.push_back(a[i].second);
    }
    sort(all(xs));
    for (ll i = 0; i < n; ++i) {
        a[i].first = lower_bound(all(xs), a[i].first) - xs.begin();
        a[i].second = lower_bound(all(xs), a[i].second) - xs.begin();
    }
    vector <Query> qs;
    for (ll i = 0; i < n; ++i) {
        qs.push_back({a[i].first, 1});
        qs.push_back({a[i].second, 0});
    }
    vector <ll> cnt(2 * n, 0);
    ll cur = 0, i = 0;
    sort(all(qs));
    for (auto q : qs) {
        if (q.opens) {
            cur++;
        } else {
            cur--;
        }
        cnt[i] = cur;
        ++i;
    }
    ST st(cnt);
    vector <ll> ans(n);
    for (ll i = 0; i < n; ++i) {
        ans[i] = max(0ll, i + 2 - st.get(i, 2 * n - i - 1)) / 2;
    }
    while (m--) {
        ll k;
        cin >> k;
        k--;
        cout << ans[k] << ' ';
    }
}