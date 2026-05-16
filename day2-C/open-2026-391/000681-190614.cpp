#include<bits/stdc++.h>
using namespace std;
#define int long long
const int pr = 998244353;
const int inf = 1e18;
struct node {
    int sum, push;
    node() {
        sum = 0; push = 0;
    }
    node(int a, int b) {
        sum = 0; push = b;
    }
};
struct seg_tree {
    vector<node> tree;
    seg_tree(int n) {
        tree.resize(n*4);
    }
    node merge_node(node a, node b) {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }
    void apply(int v, int l, int r, int x) {
        tree[v].sum += x*(r-l);
        tree[v].push += x;
    }
    void push(int v, int l, int r) {
        int x = tree[v].push;
        int m = (r + l)/2;
        apply(2*v+1, l, m, x);
        apply(2*v+2, m, r, x);
        tree[v].push += 0;
    }
    node get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) {
            return node();
        }
        if (tl >= l && tr <= r) {
            return tree[v];
        }
        push(v, tl, tr);
        int tm = (tr+tl)/2;
        return merge_node(get(2*v+1, tl, tm, l, r), get(2*v+1, tm, tr, l, r));
    }
    void upd(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) {
            return ;
        }
        if (tl >= l && tr <= r) {
            apply(v, tl, tr, x);
            return;
        }
        push(v, tl, tr);
        int tm = (tr+tl)/2;
        upd(2*v+1, tl, tm, l, r, x);
        upd(2*v+1, tm, tr, l, r, x);
        tree[v] = merge_node(tree[2*v+1], tree[2*v+2]);
    }
};
void dejkstra(vector<vector<pair<int, int>>> &g, vector<int> &dist, int v, int n) {
    dist.resize(n, inf);
    dist[v] = 0;
    set<pair<int, int>> q;
    q.insert({0, v});
    while (!q.empty()) {
        auto [w, v] = *q.begin();
        q.erase(q.begin());
        for (auto [weight, u] : g[v]) {
            if (dist[u] > dist[v] + weight) {
                q.erase({dist[u], u});
                dist[u] = dist[v] + weight;
                q.insert({dist[u], u});
            }
        }
    }
}
struct dsu {
    vector<int> pred;
    vector<int> sz;
    dsu(int n) {
        pred.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            pred[i] = i;
        }
    }
    int get(int v) {
        if (pred[v] == v) return v;
        return pred[v] = get(pred[v]);
    }
    void unite(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        pred[v] = u;
        sz[u] += sz[v];
    }
};
int fast_step(int a, int step) {
    if (step == 0) {
        return 1;
    }
    if (step%2==0) {
        int tmp = fast_step(a, step/2)%pr;
        return tmp*tmp%pr;
    }
    return (a*fast_step(a, step-1))%pr;
}

signed main() {
    ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    int l, r;
    for (int i = 0; i < n; i++) {
        cin >> l >> r;
    }
    vector<int> res;
    for (int i = 0; i < q; i++) {
        cin >> l;
        res.push_back(l/2);
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << " ";
    }
    return 0;
}