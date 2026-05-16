//#pragma GCC optimize("O3,unroll-loops")
///#pragma GCC optimize("Ofast")
#include <vector>
//#pragma GCC target("avx2")
#include <bits/stdc++.h>

using namespace std;

#define int long long
using ld = long double;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int mod = 998244353;

int binpow(int x, int n) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        return binpow(x*x%mod, n/2);
    }
    return binpow(x*x%mod, n/2) * x % mod;
}

struct Node {
    int x;
};

const int MAXN = 1e5;
vector <Node> segtree(MAXN*4);
vector <int> sum_push(MAXN*4, 0);
vector <int> arr(MAXN, 0);

Node mergeupd(Node ansl, Node ansr) {
    Node ans;
    ans.x = max(ansl.x, ansr.x);
    return ans;
}

int mergeget(int g1, int g2) {
    return max(g1, g2);
}

void push(int v) {
    segtree[v*2+1].x += sum_push[v];
    segtree[v*2+2].x += sum_push[v];
    sum_push[v*2+1] += sum_push[v];
    sum_push[v*2+2] += sum_push[v];
    sum_push[v] = 0;
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        segtree[v].x = arr[l];
        return;
    }
    int mid = (r+l)/2;
    build(v*2+1, l, mid);
    build(v*2+2, mid, r);
    segtree[v] = mergeupd(segtree[v*2+1], segtree[v*2+2]);
}

void update(int ql, int qr, int x, int v, int l, int r) {
    if (ql <= l && r <= qr) {
        segtree[v].x += x;
        sum_push[v] += x;
        return;
    }
    if (qr <= l || r <= ql) {
        return;
    }
    int mid = (r+l)/2;
    push(v);
    update(ql, qr, x, v*2+1, l, mid);
    update(ql, qr, x, v*2+2, mid, r);
}

int get(int ql, int qr, int v, int l, int r) {
    if (ql <= l && r <= qr) {
        return segtree[v].x;
    }
    if (l <= qr || r <= ql) {
        return 0;
    }
    int mid = (r+l)/2;
    push(v);
    auto g1 = get(ql, qr, v*2+1, l, mid);
    auto g2 = get(ql, qr, v*2+2, mid, r);
    return mergeget(g1, g2);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    int q;
    cin >> n >> q;
    vector <pair <int, int>> v(0);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, 0});
        v.push_back({r, 1});
    }
    sort(v.begin(), v.end());
    vector <int> ans(n+1, n);
    vector <int> pref(n*2+1, 0);
    int k1 = 0;
    int k2 = n;
    int k3 = 0;
    for (int i = 0; i < n*2; i++) {
        if (v[i].second == 0) {
            k2--;
            k3++;
        } else {
            k3--;
            k1++;
        }
        for (int j = 0; j <= 2 * min(k1, k2); j++) {
            ans[j+k3] = min(ans[j+k3], (j+1) / 2);
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << '\n';
    }
}
