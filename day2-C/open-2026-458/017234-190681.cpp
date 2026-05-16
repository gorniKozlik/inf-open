#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

struct Node {
    int max;
    int add = 0;
};

class SegTree {
 private:
    int sz;
    vector<Node> t;
 public:
    SegTree(const vector<int>& data) {
        sz = data.size();
        t.resize(4*sz);
        build(1, 0, sz, data);
    }

    Node merge(const Node& a, const Node& b) {
        Node res;
        res.max = max(a.max, b.max);
        return res;
    }

    void build(int v, int l, int r, const vector<int>& data) {
        if (l + 1 == r) {
            t[v].max = data[l];
            return;
        }
        int m = (l + r) / 2;
        build(2*v, l, m, data);
        build(2*v+1, m, r, data);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    void apply(int v, int add) {
        t[v].max += add;
        t[v].add += add;
    }

    void push(int v) {
        if (t[v].add == 0) return;
        apply(2*v, t[v].add);
        apply(2*v+1, t[v].add);
        t[v].add = 0;
    }

    void upd(int v, int vl, int vr, int ql, int qr, int x) {
        if (ql >= vr || qr <= vl) {
            return;
        } else if (vl >= ql && vr <= qr) {
            apply(v, x);
            return;
        }
        push(v);
        int m = (vl + vr) / 2;
        upd(2*v, vl, m, ql, qr, x);
        upd(2*v+1, m, vr, ql, qr, x);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    Node get(int v, int vl, int vr, int ql, int qr) {
        if (ql >= vr || qr <= vl) {
            return {-1};
        } else if (vl >= ql && vr <= qr) {
            return t[v];
        }
        push(v);
        int m = (vl + vr) / 2;
        return merge(get(2*v, vl, m, ql, qr), get(2*v+1, m, vr, ql, qr));
    }

    int getmax() {
        return get(1, 0, sz, 0, sz).max;
    }

    void update(int L, int R, int x) {
        upd(1, 0, sz, L, R, x);
    }
};


vector<int> segs(const set<pair<int, int>>& v) {
    vector<pair<int, int>> events;
    for (auto [i, j] : v) {
        events.push_back({i, -1});
        events.push_back({j, 1});
    }
    sort(events.begin(), events.end());
    vector<int> ans;
    int t = 0;
    for (int i = 0; i < events.size(); i++) {
        t += events[i].second;
        ans.push_back(t);
    }
    return ans;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> cord;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
        cord.push_back(a);
        cord.push_back(b);
    }
    sort(cord.begin(), cord.end());
    map<int, int> mp;
    for (int x : cord) mp[x] = mp.size();
    set<pair<int, int>> r;
    set<pair<int, int>, greater<pair<int, int>>> l;
    for (int i = 0; i < n; i++) {
        int a = v[i].first;
        int b = v[i].second;
        r.insert({mp[b], mp[a]});
        l.insert({mp[a], mp[b]});
    }
    vector<int> start = segs(r);
    //for (int x : start) cout << x << ' ';
    //cout << '\n';
    SegTree t(start);
    vector<int> ans(n+1, 0);
    int prev = t.getmax()+1;
    for (int k = 0; k < n; k++) {
        pair<int, int> p1 = *r.begin();
        pair<int, int> p2 = *l.begin();
        if (p1.first > p2.first) break;
        pair<int, int> p3 = {p1.second, p2.second};
        pair<int, int> p4 = {p1.first, p2.first};
        t.update(p4.first, p4.second, 2);
        r.erase(p1);
        r.erase({p2.second, p2.first});
        r.insert({p3.second, p3.first});
        r.insert({p4.second, p4.first});
        l.erase({p1.second, p1.first});
        l.erase(p2);
        l.insert(p3);
        l.insert(p4);
        int res = t.getmax();
        for (int j = prev; j <= res; j++) {
            ans[j] = k+1;
        }
        prev = res+1;
        if (prev == n+1) break;
    }

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
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
