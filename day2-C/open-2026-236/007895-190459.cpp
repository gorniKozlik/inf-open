//#define NDEBUG
//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using ll = long long;

using std::vector;
using std::make_pair;
using std::pair;

template<typename T>
void print(std::vector<T> a) {
    for (const T &i: a) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

struct sgt {
    std::vector<int> t, d;

    sgt(int n) : t(n * 4), d(n * 4) {
    }

    void push(int v) {
        d[2 * v + 1] += d[v];
        d[2 * v + 2] += d[v];
        t[2 * v + 1] += d[v];
        t[2 * v + 2] += d[v];
        d[v] = 0;
    }

    void add(int v, int l, int r, int ql, int qr, int x) {
        if (l >= qr || ql >= r) {
            return;
        }
        if (ql <= l && r <= qr) {
            t[v] += x;
            d[v] += x;
            return;
        }
        push(v);
        int mid = (l + r) / 2;
        add(2 * v + 1, l, mid, ql, qr, x);
        add(2 * v + 2, mid, r, ql, qr, x);
        t[v] = std::max(t[2 * v + 1], t[2 * v + 2]);
    }

    int q(int v, int l, int r, int ql, int qr) {
        if (l >= qr || ql >= r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }
        push(v);
        int mid = (l + r) / 2;
        return std::max(q(2 * v + 1, l, mid, ql, qr), q(2 * v + 2, mid, r, ql, qr));
    }
};

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> l(n), r(n);
    std::vector<int> lr(2 * n);
    for (int i = 0; i < n; ++i) {
        std::cin >> l[i] >> r[i];
        lr[2 * i] = l[i];
        lr[2 * i + 1] = r[i];
    }
    std::set<int> ls, rs;
    std::sort(lr.begin(), lr.end());
    for (int i = 0; i < n; ++i) {
        l[i] = std::lower_bound(lr.begin(), lr.end(), l[i]) - lr.begin();
        r[i] = std::lower_bound(lr.begin(), lr.end(), r[i]) - lr.begin();
        ls.insert(l[i]);
        rs.insert(r[i]);
    }

    sgt t(2 * n + 1);

    for (int i = 0; i < n; ++i) {
        t.add(0, 0, 2 * n + 1, l[i], r[i] + 1, 1);
    }


    std::vector<int> ans(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (t.q(0, 0, n, 0, 2 * n + 1) <= i && !ls.empty() && !rs.empty()) {
            int l1 = *ls.rbegin();
            int r1 = *rs.begin();
            rs.erase(rs.begin());
            ls.erase(--ls.end());
            t.add(0, 0, 2 * n + 1, r1 + 1, l1, 2);
            t.add(0, 0, 2 * n + 1, r1, r1 + 1, 1);
            t.add(0, 0, 2 * n + 1, l1, l1 + 1, 1);
            ++cnt;
        }
        ans[i] = cnt;
    }
    std::vector<int> k(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> k[i];
        std::cout << ans[k[i] - 1] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
