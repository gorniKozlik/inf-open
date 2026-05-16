#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <queue>

using namespace std;
using ll = long long;
using ld = long double;

#define int ll

const int MOD = 998'244'353;
const int SIGNES = 6;
const int INF = 1e9;

void push(vector<pair<int, int>> &tree, int i, int l, int r) {
    tree[i].first = max(tree[i].first, tree[i].second);
    if (r - l != 1) {
        int push = tree[i].second;
        tree[i * 2].second = max(tree[i * 2].second, push);
        tree[i * 2 + 1].second = max(tree[i * 2 + 1].second, push);
    }
    tree[i].second = 0;
}

void update(vector<pair<int, int>> &tree, int i, int l, int r, int ql, int qr, int x) {
    push(tree, i, l, r);
    if (l >= qr or r <= ql) {
        return;
    }
    if (ql <= l and r <= qr) {
        tree[i].second = max(tree[i].second, x);
        push(tree, i, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(tree, i * 2, l, m, ql, qr, x);
    update(tree, i * 2 + 1, m, r, ql, qr, x);
    tree[i].first = max(tree[i * 2].first, tree[i * 2 + 1].first);
}

int get(vector<pair<int, int>> &tree, int i, int l, int r, int qi) {
    push(tree, i, l, r);
    if (l > qi or r <= qi) {
        return -1e9;
    }
    if (r - l == 1) {
        return tree[i].first;
    }
    int m = (l + r) / 2;
    return max(get(tree, i * 2, l, m, qi), get(tree, i * 2 + 1, m, r, qi));
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
    }
    vector<pair<int, int>> idk;
    for (auto &i : a) {
        idk.emplace_back(i.first, 1);
        idk.emplace_back(i.second, 0);
    }
    sort(idk.begin(), idk.end());
    vector<int> lol;
    for (auto &i : idk) {
        lol.push_back(i.second);
    }
    int m = lol.size();
    vector<int> pref(m);
    for (int i = 0; i < m; i++) {
        pref[i] = (i > 0? pref[i - 1] : 0) + lol[i];
    }
    int last = 2 * m;
    vector<pair<int, int>> tree(4 * last);
    int open = 0;
    for (int i = 0; i < m; i++) {
        if (lol[i] == 1) {
            open++;
        } else {
            open--;
        }
        int minus = (i + 1) - pref[i];
        int pluses = (pref.back() - pref[i]);
        update(tree, 1, 0, last, 0, open + 2 * min(minus, pluses) + 1, open);
    }
    while (q--) {
        int k;
        cin >> k;
        // k *= 2;
        int ans = max((k - get(tree, 1, 0, last, k) + 1) / 2, 0ll);
        // int open = 0;
        // for (int i = 0; i < m; i++) {
        //     if (lol[i] == 1) {
        //         open++;
        //     } else {
        //         open--;
        //     }
        //     int minus = (i + 1) - pref[i];
        //     int pluses = (pref.back() - pref[i]);
        //     if (open + 2 * min(minus, pluses) >= k) {
        //         ans = min(ans, max((k - open + 1) / 2, 0ll));
        //     }
        // }
        cout << ans << '\n';
    }
}

signed main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(SIGNES);

    int q = 1;

    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
    #endif

    while (q--) {
        solve();
    }

}