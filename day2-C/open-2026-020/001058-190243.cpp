#define _GLIBCXX_FILESYSTEM
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int l[MAXN], r[MAXN];

void compress(int n) {
    vector <tuple <int, int, int>> v;

    for (int i = 1; i <= n; i++) {
        v.push_back({l[i], 0, i});
        v.push_back({r[i], 1, i});
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        auto [val, t, idx] = v[i];
        if (t == 0) l[idx] = i;
        else r[idx] = i;
    }
}

int segment[8 * MAXN], lazy[8 * MAXN];

void push_lazy(int idx, int l, int r) {
    if (lazy[idx] == 0 || l == r) return;

    segment[2 * idx] += lazy[idx];
    segment[2 * idx + 1] += lazy[idx];
    lazy[2 * idx] += lazy[idx];
    lazy[2 * idx + 1] += lazy[idx];

    lazy[idx] = 0;
}

int update(int idx, int l, int r, int ql, int qr, int val) {
    if (qr < l || r < ql) return segment[idx];
    if (ql <= l && r <= qr) {
        lazy[idx] += val;
        return segment[idx] += val;
    }

    push_lazy(idx, l, r);
    int m = (l + r) / 2;
    return segment[idx] = max(update(2 * idx, l, m, ql, qr, val), update(2 * idx + 1, m + 1, r, ql, qr, val));
}

int query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return segment[idx];

    push_lazy(idx, l, r);
    int m = (l + r) / 2;
    return max(query(2 * idx, l, m, ql, qr), query(2 * idx + 1, m + 1, r, ql, qr));
}

int ans[4 * MAXN];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }

    compress(n);

    set <int> plus, minus;

    int s = 2 * n + 1;

    for (int i = 1; i <= n; i++) {
        plus.insert(l[i]);
        minus.insert(r[i]);

        update(1, 1, s, l[i], r[i] - 1, 1);
        //cout << "Updating range [" << l[i] << ", " << r[i] << "] by 1.\n";
    }

    int moves = 0;

    ans[moves] = query(1, 1, s, 1, s);

    while (++moves) {
        auto mit = minus.begin();
        auto pit = prev(plus.end());

        int m = *mit;
        int p = *pit;

        if (p < m) break;
        
        plus.erase(pit);
        minus.erase(mit);

        plus.insert(m);
        minus.insert(p);

        update(1, 1, s, m, p - 1, 2);
        ans[moves] = query(1, 1, s, 1, s);

        //cout << "In " << moves << " moves we can achieve beauty " << ans[moves] << '\n';
    }

    ans[moves] = INT_MAX;

    while (q--) {
        int t;
        cin >> t;

        int idx = lower_bound(ans, ans + moves, t) - ans;
        cout << idx << ' ';
    }

    return 0;

}