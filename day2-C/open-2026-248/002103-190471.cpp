#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxn = 2e5 + 5;
int st[4 * maxn], mod[4 * maxn];

void push(int v) {
    st[2*v] += mod[v];
    st[2*v+1] += mod[v];
    mod[2*v] += mod[v];
    mod[2*v+1] += mod[v];
    mod[v] = 0;
}

void add(int v, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        st[v] += x;
        mod[v] += x;
        return;
    }
    push(v);

    int m = (l + r) / 2;
    add(2*v, l, m, ql, qr, x);
    add(2*v+1, m, r, ql, qr, x);

    st[v] = max(st[2*v], st[2*v+1]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector <pair <int, int>> p(n), p1(n);
    set <pair <int, int>> ps;
    vector <int> ks(q);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        ps.emplace(p[i].first, 1);
        ps.emplace(p[i].second, -1);

        add(1, 0, maxn, p[i].first, p[i].second, 1);
    }
    p1 = p;

    for (int i = 0; i < q; i++) {
        cin >> ks[i];
    }

    sort(p.begin(), p.end(), [](auto i, auto j) {
        return i.first < j.first;
    });

    sort(p1.begin(), p1.end(), [](auto i, auto j) {
        return i.second > j.second;
    });

    vector <int> ans(n+1, 1e9);
    int cntused = 0;

    int cntcur = 0;
    for (auto i : ps) {
        cntcur += i.second;
        ans[cntcur] = min(ans[cntcur], cntused);
    }

    while (!p.empty()) {
        auto vl = p.back();
        auto vr = p1.back();
        p.pop_back();
        p1.pop_back();
        cntused++;

        if (vr.second > vl.first) {
            break;
        }
        add(1, 0, maxn, vr.second, vl.first, 2);

        // ps.erase(ps.find({vr.second, -1}));
        // ps.erase(ps.find({vl.first, 1}));
        // ps.emplace(vl.first, -1);
        // ps.emplace(vr.second, 1);

        // int cntcur = 0;
        // for (auto i : ps) {
        //     cntcur += i.second;
        //     ans[cntcur] = min(ans[cntcur], cntused);
        // }

        ans[st[1]] = min(ans[st[1]], cntused);
    }

    for (int i = n-1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i+1]);
    }

    for (auto i : ks) {
        cout << ans[i] << '\n';
    }
}
