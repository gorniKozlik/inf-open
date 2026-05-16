#include<bits/stdc++.h>

#define len(v) (int)v.size()
#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long int;
using ld = long double;

const int MAXN = 2e5 + 10;

struct ST{
    vector<ll> tree;
    ST() {}
    ST(int n) {
        tree.resize(2 * n - 1, -1e9);
    }
    void change(int v, int l, int r, int askl, int askr, ll val) {
        if (l >= askr || r <= askl) return;
        if (l >= askl && r <= askr) {
            tree[v] = max(tree[v], val);
            return;
        }
        int m = (l + r) / 2, left = v + 1, right = v + 2 * (m - l);
        change(left, l, m, askl, askr, val);
        change(right, m, r, askl, askr, val);
    }
    ll ask(int v, int l, int r, int pos) {
        if (l == r - 1) {
            return tree[v];
        }
        int m = (l + r) / 2, left = v + 1, right = v + 2 * (m - l);
        if (pos < m) return max(ask(left, l, m, pos), tree[v]);
        else return max(ask(right, m, r, pos), tree[v]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        b.push_back(a[i].first);
        b.push_back(a[i].second);
    }
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    map<int, int> m;
    for (int i = 0; i < len(b); ++i) {
        m[b[i]] = i;
    }
    vector<int> ind(2 * n);
    vector<bool> start(2 * n, false);
    for (int i = 0; i < n; ++i) {
        a[i].first = m[a[i].first];
        start[a[i].first] = true;
        a[i].second = m[a[i].second];
    }
    vector<int> anses(n + 1, 1e9);
    int left = 0, right = n, now = 0;
    ST k2(MAXN), k1(MAXN);
    for (int i = 0; i < 2 * n; ++i) {
        if (start[i]) {
            now++;
            --right;
        }
        int mn = min(left, right);
        int ost = max(left, right) - mn;
        k2.change(0, 0, MAXN, 0, mn + 1, now);
        k1.change(0, 0, MAXN, mn, MAXN, now + mn);
        if (!start[i]) {
            now--;
            left++;
        }
    }
    for (int i = 0; i <= n; ++i) {
        anses[i] = max(k2.ask(0, 0, MAXN, i) + i * 2, k1.ask(0, 0, MAXN, i) + i);
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        int left = -1, right = n;
        while (left != right - 1) {
            int mid = (left + right) / 2;
            if (anses[mid] >= k) {
                right = mid;
            } else {
                left = mid;
            }
        }
        cout << right << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
}