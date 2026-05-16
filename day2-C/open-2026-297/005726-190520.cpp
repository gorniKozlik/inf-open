#include <bits/stdc++.h>

#define all(a) a.begin(), a.end()
#define pb push_back
#define lb lower_bound

using ll = long long;
using namespace std;

const int mod = 998244353;
const ll inf = 1e18;
const int k = 475;

struct event {
    int x, type, i;
    bool operator<(const event f) const {
        return tie(x, type) < tie(f.x, f.type);
    }
};

void read() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

struct Node {
    int left, right, sum, best;
};

struct segtree {
    int sz; vector<Node> t;
    segtree(int n, vector<int>&a) {
        sz = n; t.assign(4 * sz + 1, {});
        build(1, 0, sz, a);
    }

    void upd(int v) {
        t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
        t[v].left = min({t[2 * v].left, t[2 * v].sum + t[2 * v + 1].left, t[v].sum});
        t[v].right = min({t[2 * v + 1].right, t[2 * v + 1].sum + t[2 * v].right, t[v].sum});
        t[v].best = min({t[v].sum, t[v].left, t[v].right, t[2 * v].left + t[2 * v + 1].right});
    }

    void build(int v, int l, int r, vector<int> &a) {
        if (l == r - 1) {
            t[v] = Node{a[l], a[l], a[l], a[l]};
            return;
        }

        int mid = (l + r)/2;
        build(2 * v, l, mid, a);
        build(2 * v + 1, mid, r, a);
        upd(v);
    }

    void add(int v, int l, int r, int i, int x) {
        if (l == r - 1) {
            t[v] = Node{x, x, x, x};
            return;
        }

        int mid = (l + r)/2;
        if (i < mid) {
            add(2 * v, l, mid, i, x);
        } else {
            add(2 * v + 1, mid, r, i, x);
        }

        upd(v);
    }
};

int main() {
    read();

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
    }

    vector<int> ans(n + 1), query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i];
    }

    set<pair<int, int>> R; set<pair<int, int>, greater<>> L;
    for (int i = 0; i < n; i++) {
        L.insert({seg[i].first, i});
        R.insert({seg[i].second, i});
    }

    vector<event> s;
    for (int i = 0; i < n; i++) {
        s.pb(event{seg[i].first, -1, i});
        s.pb(event{seg[i].second, 1, i});
    }

    sort(all(s));

    int M = s.size();

    unordered_map<int, pair<int, int>> T;
    for (int i = 0; i < M; i++) {
        if (s[i].type == -1) {
            T[s[i].i].first = i;
        }

        if (s[i].type == 1) {
            T[s[i].i].second = i;
        }
    }

    vector<int> val(M);
    for (int i = 0; i < M; i++) {
        val[i] = s[i].type;
    }

    segtree st(M, val);

    int j = 1, F = 0;
    while (j <= -st.t[1].best) {
        ans[j] = F;
        j++;
    }

    F++;

    while (j <= n) {
        int v = R.begin()->second,
            u = L.begin()->second;
        R.erase(R.begin());
        L.erase(L.begin());
        int a = T[v].second, b = T[u].first;
        swap(seg[v].second, seg[u].first);
        st.add(1, 0, M, a, -1);
        st.add(1, 0, M, b, 1);
        int res = -st.t[1].best;
        while (j <= res) {
            ans[j] = F;
            j++;
        }
        F++;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[query[i]] << " ";
    }

    cout << "\n";
}
