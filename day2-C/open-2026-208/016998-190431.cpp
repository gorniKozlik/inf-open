//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using ll = long long;
using ld = long double;

const int MOD = 998244353;
const int INFi = 1e9;
const ll INF = 1e18;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int bin_pow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) {
            res = res * 1ll * x % MOD;
        }
        y >>= 1;
        x = x * 1ll * x % MOD;
    }
    return res;
}

struct SegmentTree {
    int size;
    vector<pair<int, int>> tree;
    SegmentTree(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        tree.resize(size * 2 - 1);
    }
    void push(int v) {
        if (tree[v].second == 0) {
            return;
        }
        apply(v, v * 2 + 1);
        apply(v, v * 2 + 2);
        tree[v].second = 0;
    }
    void apply(int v1, int v2) {
        tree[v2].first += tree[v1].second;
        tree[v2].second += tree[v1].second;
    }
    void upd(int v, int lx, int rx, int l, int r, int val) {
        if (r <= lx || rx <= l) {
            return;
        }
        if (lx <= l && r <= rx) {
            tree[v].second += val;
            tree[v].first += val;
            return;
        }
        push(v);
        int m = (l + r) >> 1;
        upd(v * 2 + 1, lx, rx, l, m, val);
        upd(v * 2 + 2, lx, rx, m, r, val);
        tree[v].first = max(tree[v * 2 + 1].first, tree[v * 2 + 2].first);
    }
    void upd(int l, int r, int val) {
        upd(0, l, r, 0, size, val);
    }
    int get() {
        return tree[0].first;
    }
};

bool cmp2(pair<int, int>& x, pair<int, int>& y) {
    return x.first < y.first;
}

bool cmp1(pair<int, int>& x, pair<int, int>& y) {
    return x.second < y.second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> coord;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        coord.push_back(a[i].first);
        coord.push_back(a[i].second);
    }
    vector<int> w(q);
    for (int i = 0; i < q; i++) {
        cin >> w[i];
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    int len = (int)coord.size();
    //vector<int> cnt_used(len * 4), used(len * 4);
    map<int, int> cnt_used, used;
    for (int i = 0; i < n; i++) {
        a[i].first = lower_bound(coord.begin(), coord.end(), a[i].first) - coord.begin();
        a[i].second = lower_bound(coord.begin(), coord.end(), a[i].second) - coord.begin();
        //cout << a[i].first << ' ' << a[i].second << ' ' << len * 4 << endl;
        cnt_used[a[i].first * len + a[i].second]++;

    }
    vector<pair<int, int>> min_left = a, max_right = a;
    sort(min_left.begin(), min_left.end(), cmp1);
    sort(max_right.begin(), max_right.end(), cmp2);

    len *= 2;
    SegmentTree tree(len);
    for (int i = 0; i < n; i++) {
        tree.upd(a[i].first, a[i].second + 1, 1);
    }
    //cout << 777 << endl;
    vector<int> res(n + 1, INFi);
    int mx = tree.get();
    res[mx] = 0;
    int left = 0, right = n - 1, tt = 0;
    for (; left < n && right >= 0;) {
        //cout << left << ' ' << right << endl;
        //cout << left << ' ' << min_left[left].first * len + min_left[left].second << endl;
        while (left < n && cnt_used[min_left[left].first * len + min_left[left].second] == used[min_left[left].first * len + min_left[left].second]) {
            left++;
        }
        if (left < n) {
            used[min_left[left].first * len + min_left[left].second]++;
        }
        while (right >= 0 && cnt_used[max_right[right].first * len + max_right[right].second] == used[max_right[right].first * len + max_right[right].second] || left == right) {
            right--;
        }
        if (right >= 0) {
            used[max_right[right].first * len + max_right[right].second]++;
        }
        //cout << left << ' ' << right << endl;
        if (left < n && right >= 0) {
            tree.upd(min_left[left].first, min_left[left].second + 1, -1);
            tree.upd(max_right[right].first, max_right[right].second + 1, -1);
            //cout << tt << ' ' << left << ' ' << right << endl;
            int nl1 = min_left[left].first;
            int nr1 = max_right[right].second;
            int nl2 = min_left[left].second;
            int nr2 = max_right[right].first;
            //cout << nl1 << ' ' << nr1 << ' ' << nl2 << ' ' << nr2 << ' ' << len << endl;
            tree.upd(nl1, nr1 , 1);
            tree.upd(nl2, nr2 , 1);
        }
        mx = tree.get();
        res[mx] = min(res[mx], ++tt);
    }
    for (int i = n - 1; i >= 1; i--) {
        res[i] = min(res[i], res[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        cout << res[w[i]] << ' ';
    }
    cout << '\n';
}
