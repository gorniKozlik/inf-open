#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Monster {
    ll h; ll r;
};

struct Weapon {
    ll s, c;
};

const int MAXN = 5;
ll tree_w[MAXN * 4];
ll w[MAXN];

void build_w(int v, int tl, int tr) {
    if (tr - tl == 1) {
        tree_w[v] = w[tl];
        return;
    }
    int m = (tl + tr) / 2;
    build_w(v * 2 + 1, tl, m);
    build_w(v * 2 + 2, m, tr);
    tree_w[v] = min(tree_w[v * 2 + 1], tree_w[v * 2 + 2]);
}

ll query_w(int v, int l, int r, int tl, int tr) {
    if (tr <= l || r <= tl) return LLONG_MAX;
    if (l <= tl && tr <= r) return tree_w[v];
    int m = (tl + tr) /2;
    return min(query_w(v * 2 + 1, l, r, tl, m),
        query_w(v * 2 + 2, l, r, m, tr));
}

ll mm[MAXN];
ll tree_m[MAXN * 4];

void build_m(int v, int tl, int tr) {
    if (tr - tl == 1) {
        tree_m[v] = mm[tl];
        return;
    }

    int mid = (tl + tr) / 2;
    build_m(v * 2 + 1, tl, mid);
    build_m(v * 2 + 2, mid, tr);
    tree_m[v] = max(tree_m[v * 2 + 1], tree_m[v * 2 + 2]);
}

ll query_m(int v, int l, int r, int tl, int tr) {
    if (tr <= l || r <= tl) return LLONG_MIN;
    if (l <= tl && tr <= r) return tree_m[v];
    int m = (tl + tr) / 2;
    return max(query_m(v * 2 + 1, l, r, tl, m),
        query_m(v * 2 + 2, l, r, m, tr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    ll x;
    cin >> n >> m >> k >> x;

    vector<ll> pref_r(n + 1, 0LL);
    vector<Monster> p(n);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i - 1].h >> p[i - 1].r;
        mm[i - 1] = p[i - 1].h;
        pref_r[i] = pref_r[i - 1] + p[i - 1].r;
    }

    vector<Weapon> weapon(m);
    for (auto &[s, c] : weapon) cin >> s >> c;
    sort(weapon.begin(), weapon.end(), [&](const Weapon &a, const Weapon &b) {
        return a.s < b.s;
    });

    for (int i = 0; i < MAXN * 4; ++i)
        tree_w[i] = LLONG_MAX;
    for (int i = 0; i < m; ++i)
        w[i] = weapon[i].c;

    build_w(0, 0, m);
    build_m(0, 0, n);
    int cur = 0;
    while (cur != n) {
        bool found = false;
        int last;
        for (int i = n; i > cur; --i) {
            ll mxh = query_m(0, cur, i, 0, n);
            int left = -1, right = m;
            while (left + 1 < right) {
                int mid = (left + right) / 2;
                if (weapon[mid].s < mxh)
                    left = mid;
                else
                    right = mid;
            }
            if (right == m) {
                cout << "No\n";
                return 0;
            }
            ll cost = query_w(0, right, m, 0, m);
            if (cost <= x) {
                last = i;
                x -= cost;
                x += pref_r[last] - pref_r[cur];
                found = true;
                cur = last;
                break;
            }
        }
        if (!found) {
            cout << "No\n";
            return 0;
        }
        cur = last;
    }
    cout << "Yes\n";
    return 0;

}
