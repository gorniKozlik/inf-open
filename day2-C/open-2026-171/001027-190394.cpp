#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int INF = 1e9;

vector<int> tree;
vector<int> p;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = 0;
}

void push(int v) {
    int x = p[v];
    if (x == 0) {
        return;
    }
    if (tree[2 * v + 1] < x) {
        tree[2 * v + 1] = x;
        p[2 * v + 1] = x;
    }
    if (tree[2 * v + 2] < x) {
        tree[2 * v + 2] = x;
        p[2 * v + 2] = x;
    }
    p[v] = 0;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (ql >= r || l >= qr) {
        return;
    }
    if (ql <= l && r <= qr) {
        if (tree[v] < x) {
            tree[v] = x;
            p[v] = x;
        }
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v + 2, l, m, ql, qr, x);
    update(2 * v + 2, m, r, ql, qr, x);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (ql >= r || l >= qr) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<pair<int, int> > sc(0);
    for (int i = 0; i < n; i++) {
        a[i].first *= 2;
        a[i].second *= 2;
        sc.push_back({a[i].first, -1});
        sc.push_back({a[i].second, 1});
        sc.push_back({a[i].first + 1, 0});
        sc.push_back({a[i].first - 1, 0});
        sc.push_back({a[i].second + 1, 0});
        sc.push_back({a[i].second - 1, 0});
    }
    int otk = 0, z = 0;
    sort(sc.begin(), sc.end());
    vector<int> dp(n + 1, 0);
    for (int i = 0; i < sc.size(); i++) {
        int type = sc[i].second;
        if (type == -1) {
            otk++;
        }
        if (type == 1) {
            otk--;
            z++;
        }
        if (type == 0) {
            int otr = otk;
            int h = 2 * n - 2 * otr - 2 * z;
            int l = h / 2;
            int ss = otr + 2 * min(l, z);
            if (otr + 2 * min(l, z) >= 1) {
                //update(0, 1, n + 1, 1, otr + 2 * min(l, z) + 1, otr);
                dp[ss] = max(dp[ss], otr);
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        dp[i] = max(dp[i], dp[i + 1]);
    }
    for (int i = 1; i <= q; i++) {
        int x;
        cin >> x;
        int h = dp[x];
        if (h >= x) {
            cout << 0 << " ";
            continue;
        }
        int g = (x - h + 1) / 2;
        cout << g << " ";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
