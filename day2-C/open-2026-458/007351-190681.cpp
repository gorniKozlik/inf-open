#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}

struct Node {
    int max, min;
};

int n;

class SegTree {
 private:
    int sz;
    vector<Node> t;
 public:
    SegTree(const vector<int>& data) {
        sz = data.size();
        t.resize(4*sz);
    }

    Node merge(const Node& a, const Node& b) {
        Node res;
        res.max = max(a.max, b.max);
        res.min = min(a.min, b.min);
        return res;
    }

    void build(int v, int l, int r, const vector<int>& data) {
        if (l + 1 == r) {
            t[v].max = data[l];
            t[v].min = data[l];
            return;
        }
        int m = (l + r) / 2;
        build(2*v, l, m, data);
        build(2*v+1, m, r, data);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    Node get(int v, int vl, int vr, int ql, int qr) {
        if (ql >= vr || qr <= vl) {
            return {(int)-1e9, (int)1e9};
        } else if (vl >= ql && vr <= qr) {
            return t[v];
        }
        int m = (vl + vr) / 2;
        return merge(get(2*v, vl, m, ql, qr), get(2*v+1, m, vr, ql, qr));
    }

    int getmin(int L, int R) {
        return get(1, 0, sz, L, R).min;
    }

    int getmax(int L, int R) {
        return get(1, 0, sz, L, R).max;
    }
};

void solve() {
    ll n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<pair<ll, ll>> a(n);
    vector<pair<ll, ll>> sw(m);
    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (ll i = 0; i < m; i++) {
        cin >> sw[i].first >> sw[i].second;
    }
    sort(sw.begin(), sw.end());
    vector<ll> hit(m), cost(m);
    for (ll i = 0; i < m; i++) {
        hit[i] = sw[i].first;
        cost[i] = sw[i].second;
    }
    vector<ll> sufmin(m);
    sufmin[m-1] = cost[m-1];
    for (ll i = m-2; i >= 0; i--) {
        sufmin[i] = min(sufmin[i+1], cost[i]);
    }
    vector<ll> wealth(n+1, -1);
    wealth[0] = x;
    for (ll i = 0; i < n-1; i++) {
        if (sw.back().first < a[i].first) {
            cout << "No" << '\n';
            return;
        }
        for (ll j = 0; j < m; j++) {
            ll rew = 0;
            for (ll l = 0; l < k; l++) {
                if (i + l >= n) break;
                if (hit[j] >= a[i+l].first) {
                    rew += a[i+l].second;
                    wealth[i+l+1] = max(wealth[i+l+1], wealth[i] + rew - cost[j]);
                } else break;
            }
        }
    }
    //for (ll x : wealth) cout << x << ' ';
    cout << (wealth[n] == -1 ? "No" : "Yes") << '\n';
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
