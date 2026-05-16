#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998244353;
const int INF = 1e9+7;

struct D_O {
    struct node {
        int st = INF, l, r;
    };
    vector<node>tree;

    void build(int i, int l, int r) {
        tree[i].l = l; tree[i].r = r;
        if (r-l == 1) return;
        int m = (r+l)/2;
        build(i*2+1, l, m);
        build(i*2+2, m, r);
    }

    D_O(int n) {
        tree.resize(n*4);
        build(0, 0, n);
    }

    void push(int i, int l, int r) {
        if (r-l == 1) return;
        if (tree[i].st == INF) return;
        tree[i*2+1].st = min(tree[i*2+1].st, tree[i].st);
        int m = (r+l)/2;
        tree[i*2+2].st = min(tree[i*2+2].st, m - l + tree[i].st);
    }

    void update(int i, int l, int r, int lq, int rq) {
        push(i, l, r);
        if (l >= lq && r <= rq) {tree[i].st = min(tree[i].st, l-lq); return;}
        if (l >= rq || r <= lq) return;
        int m = (r+l)/2;
        update(i*2+1, l, m, lq, rq);
        update(i*2+2, m, r, lq, rq);
    }

    int get(int i, int l, int r, int ind) {
        push(i, l, r);
        if (r-l == 1) return tree[i].st;
        int m = (r+l)/2;
        if (m > ind) return get(i*2+1, l, m, ind);
        else return get(i*2+2, m, r, ind);
    }
};

signed main() {
    int n, q; cin >> n >> q;
    vector<pair<int, int> >a(n);
    vector<pair<int, int> >op;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        op.push_back({a[i].first, 1}); // 1 - открылся
        op.push_back({a[i].second, -1});
    }
    sort(op.begin(), op.end());
    int opened = 0, closed = 0;
    vector<int>dp(n+1, -1);
    for (int i = 0; i < 2*n; i++) {
        if (op[i].second == 1) {
            opened++;
            int l = closed, r = n-opened-closed, x;
            x = min(l, r)*2;
            if (l > r) x++;
            dp[opened] = max(dp[opened], x);
        } else {
            int l = closed, r = n-opened-closed, x;
            x = min(l, r)*2;
            if (r > l) x++;
            dp[opened] = max(dp[opened], x);
            opened--;
            closed++;
        }
    }
    int n1 = n/2+2;
    D_O tree00(n1), tree01(n1), tree10(n1), tree11(n1);
    for (int i = 1; i <= n; i++) {
        if (dp[i] == -1) continue;
        if (i%2 == 1) {
            if (dp[i] % 2 == 1) {
                tree11.update(0, 0, n1, i/2, i/2 + dp[i]/2 + 1);
            } else {
                tree10.update(0, 0, n1, i/2, i/2 + dp[i]/2 + 1);
            }
        } else {
            if (dp[i] % 2 == 1) {
                tree01.update(0, 0, n1, i/2, i/2 + dp[i]/2 + 1);
            } else {
                tree00.update(0, 0, n1, i/2, i/2 + dp[i]/2 + 1);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        if (x % 2 == 0) {
            int x1 = tree00.get(0, 0, n1, x/2), x2 = tree01.get(0, 0, n1, x/2), x3 = tree11.get(0, 0, n1, x/2-1) + 1;
            cout << min(x1, min(x2, x3)) << " ";
        } else {
            int x1 = tree10.get(0, 0, n1, x/2), x2 = tree11.get(0, 0, n1, x/2), x3 = tree01.get(0, 0, n1, x/2) + 1;
            cout << min(x1, min(x2, x3)) << " ";
        }
    } cout << endl;
    return 0;
}