#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using oset = tree<
    T,
    null_type,
    less<>,
    rb_tree_tag,
    tree_order_statistics_node_update
    >;

struct RSQ {
    vector<int> segtree, push;
    int n;

    RSQ(int _n) {
        n = _n;
        segtree.assign(4 * n, 0);
        push.assign(4 * n, 0);
    }

    void make_push(int v, int l, int r) {
        int mid = (l + r) >> 1;
        push[v << 1] += push[v];
        push[v << 1 | 1] += push[v];
        segtree[v << 1] += push[v] * (mid - l + 1);
        segtree[v << 1 | 1] += push[v] * (r - (mid + 1) + 1);
        push[v] = 0;
    }

    void add(int ql, int qr, int val, int v = 1, int l = 0, int r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
            push[v] += val;
            return;
        }
        make_push(v, l, r);
        int mid = (l + r) >> 1;
        add(ql, qr, val, v << 1, l, mid);
        add(ql, qr,  val, v << 1 | 1, mid + 1, r);
        segtree[v] += segtree[v << 1] + segtree[v << 1 | 1];
    }

    int getSum(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (qr < l || ql > r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return segtree[v];
        }
        make_push(v, l, r);
        int mid = (l + r) >> 1;
        return getSum(ql, qr, v << 1, l, mid) + getSum(ql, qr, v << 1 | 1, mid + 1, r);
    }
};

struct RMQ {
    vector<int> segtree, push;
    int n;

    RMQ(int _n) {
        n = _n;
        segtree.assign(4 * n, 1e18);
        push.assign(4 * n, -1);
    }

    void make_push(int v) {
        if (push[v] != -1) {
            segtree[v << 1] = segtree[v << 1 | 1] = push[v << 1] = push[v << 1 | 1] = push[v];
        }
        push[v] = -1;
    }

    void change(int ql, int qr, int to, int v = 1, int l = 0, int r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
            push[v] = to;
            segtree[v] = to;
            return;
        }
        make_push(v);
        int mid = (l + r) >> 1;
        change(ql, qr, to, v << 1, l, mid);
        change(ql, qr, to, v << 1 | 1, mid + 1, r);
        segtree[v] = min(segtree[v << 1], segtree[v << 1 | 1]);
    }

    int getMin(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (qr < l || ql > r) {
            return 1e18;
        }
        if (ql <= l && r <= qr) {
            return segtree[v];
        }
        int mid = (l + r) >> 1;
        return min(getMin(ql, qr, v << 1, l, mid), getMin(ql, qr, v << 1 | 1, mid + 1, r));
    }
};

const int LOG = 20 + 1;

struct SparseTable {
    vector<vector<int> > sparse;
    SparseTable(int n, vector<int> &from) {
        sparse.assign(20, vector<int>(n));
        sparse[0] = from;
        int j, i;
        for (j = 1; j < LOG; j++) {
            for (i = 0; i + (1 << j) <= n; i++) {
                sparse[j][i] = min(sparse[j - 1][i], sparse[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int get(int l, int r) {
        int lg = log2(r - l + 1);
        return min(sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
    }
};

#define all(a) begin(a), end(a)

void solve() {
    int n, q;
    cin >> n >> q;

    vector<pair<int, int> > scanline;
    vector<int> endCoords, startCoords;

    vector<vector<int> > beautyAch(n + 1);

    int i;
    for (i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;

        endCoords.push_back(b);
        startCoords.push_back(a);
        scanline.emplace_back(a, 1);
        scanline.emplace_back(b, -1);
    }
    sort(all(scanline));
    sort(all(startCoords));
    sort(all(endCoords));

    int quant = 0;
    int pnt1 = 0, pnt2 = 0;
    vector<int> beautyAns(n + 1, 1e18);
    beautyAns[0] = 0;
    for (i = 0; i < 2 * n - 1; i++) {
        auto [pos, type] = scanline[i];
        auto [nextPos, nextType] = scanline[i + 1];
        quant += type;
        beautyAns[quant] = 0;

        if (!(type == 1 && nextType == -1)) {
            continue;
        }

        while (pnt1 < n && endCoords[pnt1] < pos) {
            pnt1++;
        }
        while (pnt2 < n && startCoords[pnt2] < nextPos) {
            pnt2++;
        }

        int a = pnt1;
        int b = n - pnt2;

        beautyAch[quant].push_back(min(a, b));
    }

    multiset<int> odd, even;
    vector<vector<int> > lifeTime(n + 1);
    for (i = 1; i <= n; i++) {
        beautyAns[i] = min(beautyAns[i], beautyAns[i - 1] + 1);
        for (auto &el : beautyAch[i]) {
            if (i % 2) {
                odd.insert(i);
            } else {
                even.insert(i);
            }
            if (i + 2 * el <= n) {
                lifeTime[i + 2 * el].push_back(i);
            }
        }

        if (i % 2) {
            if (odd.size()) {
                beautyAns[i] = min(beautyAns[i], beautyAns[*prev(odd.end())] + (i - *prev(odd.end())) / 2);
            }
            for (auto &el : lifeTime[i]) {
                odd.erase(odd.find(el));
            }
        } else {
            if (even.size()) {
                beautyAns[i] = min(beautyAns[i], beautyAns[*prev(even.end())] + (i - *prev(even.end())) / 2);
            }
            for (auto &el : lifeTime[i]) {
                even.erase(even.find(el));
            }
        }
    }

    while (q--) {
        int k;
        cin >> k;

        cout << beautyAns[k] << ' ';
    }
}

signed main() {
    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }
}