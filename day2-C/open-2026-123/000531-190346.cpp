#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;


#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define FOR(i, a, b) for(ll i = a; i < b; ++i)
#define ROF(i, a, b) for(ll i = b; i >= a; --i)

mt19937 rnd(42);
mt19937_64 rnd64(52);

struct SegmentTree {
    struct Node {
        ll max;
    };
    vector<Node> t;
    vector<ll> lz;
    Node neutral = {0};
    SegmentTree(ll n) {
        t.resize(4 * n);
        lz.resize(4 * n);
    }
    Node merge(Node a, Node b) {
        Node c;
        c.max = max(a.max, b.max);
        return c;
    }
    void apply(ll x, ll lx, ll rx, ll val) {
        t[x].max += val;
        lz[x] += val;
    }
    void push(ll x, ll lx, ll rx) {
        if (rx - lx == 1 || lz[x] == 0) {
            return;
        }
        ll m = rx + lx >> 1;
        apply(2*x+1, lx, m, lz[x]);
        apply(2*x+2, m, rx, lz[x]);
        lz[x] = 0;
    }
    void update(ll x, ll lx, ll rx, ll l, ll r, ll val) {
        if (l <= lx && rx <= r) {
            apply(x, lx, rx, val);
            return;
        }
        if (rx <= l || r <= lx) {
            return;
        }
        push(x, lx, rx);
        ll m = rx + lx >> 1;
        update(2*x+1, lx, m, l, r, val);
        update(2*x+2, m, rx, l, r, val);
        t[x] = merge(t[2*x+1], t[2*x+2]);
    }
    Node query(ll x, ll lx, ll rx, ll l, ll r) {
        if (l <= lx && rx <= r) {
            return t[x];
        }
        if (rx <= l || r <= lx) {
            return neutral;
        }
        push(x, lx, rx);
        ll m = rx + lx >> 1;
        Node q1 = query(2*x+1, lx, m, l, r);
        Node q2 = query(2*x+2, m, rx, l, r);
        return merge(q1, q2);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll n, q;
    cin >> n >> q;
    vector<pair<ll,ll>> v(n);
    vector<ll> v2(2 * n);
    for (ll i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
        v2[i * 2] = v[i].first;
        v2[i * 2 + 1] = v[i].second;
    }
    sort(all(v2));
    for (ll i = 0; i < n; ++i) {
        v[i].first = lower_bound(v2.begin(), v2.end(), v[i].first) - v2.begin();
        v[i].second = lower_bound(v2.begin(), v2.end(), v[i].second) - v2.begin();
    }
    ll N = 2 * n + 10;
    SegmentTree st(N);
    set<ll> l, r;
    for (ll i = 0; i < n; ++i) {
        l.insert(-v[i].first);
        r.insert(v[i].second);
        st.update(0,0,N,v[i].first,v[i].second,1);
    }
    vector<ll> ans(n + 1);
    for (ll i = 1; i <= n; ++i) {
        ans[i] = ans[i - 1];
        while (st.t[0].max < i) {
            ll R = *r.begin();
            ll L = -*l.begin();
            r.erase(r.begin());
            l.erase(l.begin());
            r.insert(L);
            l.insert(-R);
            st.update(0,0,N,R,L,2);
            ans[i]++;
        }
    }
    for (ll i=0; i < q; ++i) {
        ll x; cin >>x;
        cout<< ans[x] << " ";
    }
}