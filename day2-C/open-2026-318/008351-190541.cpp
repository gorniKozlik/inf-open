#include<bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 5e5;

struct Node {
    int val = 0;
    int push = 0;
    Node() = default;
};
// Node operator+(const Node&a, const Node&b) const {

// }
Node t[4 * MAXN];

void push(int v, int l, int r) {
    if (l + 1 == r) {
        t[v].val += t[v].push;
        t[v].push = 0;
        return;
    }
    int m = (l + r) / 2;
    t[2 * v + 1].push += t[v].push;
    t[2 * v + 2].push += t[v].push;
    t[v].val += t[v].push;
    t[v].push = 0;
}

void update(int v, int l, int r, int lq, int rq, int x) {
    push(v, l, r);
    if (rq <= l || r <= lq) return;
    if (lq <= l && r <= rq) {
        t[v].push += x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, lq, rq, x);
    update(2 * v + 2, m, r, lq, rq, x);
    t[v].val = max(t[2 * v + 1].val, t[2 * v + 2].val);
}

int get(int v, int l, int r, int lq, int rq) {
    push(v, l, r);
    if (rq <= l || r <= lq) return -1;
    if (lq <= l && r <= rq) return t[v].val;
    int m = (l + r) / 2;
    return max(get(2 * v + 1, l, m, lq, rq), get(2 * v + 2, m, r, lq, rq));
}

int count(vector<pair<int, int>>& a) {
    vector<pair<int, int>> events;
    for (int i = 0; i < a.size(); i++) {
        events.emplace_back(a[i].first, 1);
        events.emplace_back(a[i].second, -1);
    }
    sort(events.begin(), events.end());
    int cur = 0;
    int res = 0;
    for (auto [x, t]: events) {
        cur += t;
        res = max(res, cur);
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> b;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        b.push_back(a[i].first);
        b.push_back(a[i].second);
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < n; i++) {
        a[i].first = lower_bound(b.begin(), b.end(), a[i].first) - b.begin();
        a[i].second = lower_bound(b.begin(), b.end(), a[i].second) - b.begin();
    }
    sort(a.begin(), a.end());
    // int curcnt = count(a);
    set<pair<int, int>> sortl;
    set<pair<int, int>> sortr;
    for (int i = 0; i < n; i++) {
        sortl.insert({a[i].first, i});
        sortr.insert({a[i].second, i});
        update(0, 0, MAXN, a[i].first, a[i].second, 1);
    }
    int curcnt = get(0, 0, MAXN, 0, MAXN);
    vector<int> ans;
    ans.push_back(curcnt);
    while (curcnt < n) {
        auto itl = --sortl.end();
        auto itr = sortr.begin();
        int bestl = itl->second;
        int bestr = itr->second;
        // for (int i = 0; i < n; i++) {
        //     if (a[i].first > a[bestl].first) {
        //         bestl = i;
        //     }
        //     if (a[i].second < a[bestr].second) {
        //         bestr = i;
        //     }
        // }
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        int r1 = a[bestr].second;
        int l1 = a[bestl].first;
        sortl.erase({a[bestl].first, bestl});
        sortl.erase({a[bestr].first, bestr});
        sortr.erase({a[bestl].second, bestl});
        sortr.erase({a[bestr].second, bestr});
        update(0, 0, MAXN, a[bestl].first, a[bestl].second, -1);
        update(0, 0, MAXN, a[bestr].first, a[bestr].second, -1);
        a[bestl].first = r1;
        if (a[bestl].first > a[bestl].second) swap(a[bestl].first, a[bestl].second);
        a[bestr].second = l1;
        if (a[bestr].first > a[bestr].second) swap(a[bestr].first, a[bestr].second);
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        sortl.insert({a[bestl].first, bestl});
        sortl.insert({a[bestr].first, bestr});
        sortr.insert({a[bestl].second, bestl});
        sortr.insert({a[bestr].second, bestr});

        update(0, 0, MAXN, a[bestl].first, a[bestl].second, 1);
        update(0, 0, MAXN, a[bestr].first, a[bestr].second, 1);

        // curcnt = count(a);
        curcnt = get(0, 0, MAXN, 0, MAXN);
        // segment tree +=  & max


        // cout << curcnt << endl;
        ans.push_back(curcnt);
    }
    // for (int i: ans) cout << i << ' ';
    // cout << endl;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        auto it = lower_bound(ans.begin(), ans.end(), k);
        cout << it - ans.begin() << '\n';
    }
    return 0;
}