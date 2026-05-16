#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")

#define int long long

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define fi first
#define se second
#define rep(i,j,k) for (int (i) = (j); (i) < (k); ++i)
#define rrep(i,j,k) for (int (i) = (j); (i) >= (k); --i)
#define re return
#define pb push_back

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree<int, less<>, null_type, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset = tree<int, less_equal<>, null_type, rb_tree_tag, tree_order_statistics_node_update>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
using si = set<int>;
using msi = multiset<int>;

void amin(int& a, int b) {
    a = min(a, b);
}

void amax(int& a, int b) {
    a = max(a, b);
}

void solve();

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
    }
}

/* ------------------------------------- ACTUAL CODE STARTS HERE ------------------------------------- */

int n, q;
vpii segs;

struct event {
    int x, type, idx;
};

const int INF = 2e18;

vi solve1() {
    vector<event> e;
    rep(i, 0, n) {
        auto [l, r] = segs[i];
        e.pb({l, 1, i});
        e.pb({r, -1, i});
    }
    sort(all(e), [&](auto a, auto b) {
        re a.x < b.x || (a.x == b.x && a.type > b.type) || (a.x == b.x && a.type == b.type && a.idx < b.idx);
    });
    vi left, right;
    for (auto [l, r] : segs) {
        left.pb(l);
        right.pb(r);
    }
    sort(all(left));
    sort(all(right));
    vi cnts(n), ans(n + 1, INF);
    ans[0] = 0;
    int cnt = 0;
    for (auto [x, type, idx] : e) {
        cnt += type;
        int ll = lower_bound(all(right), x) - right.begin();
        int rr = upper_bound(all(left), x) - left.begin();
        rr = left.size() - rr;
        amin(ans[cnt], 0);
        int tmp_cnt = cnt, cur_ns = 0;
        tmp_cnt += 2 * min(ll, rr);
        // cout << tmp_cnt << " " << min(ll, rr) << "!!!\n";
        amin(ans[tmp_cnt], min(ll, rr));
    }
    rep(i, 1, n + 1) {
        if (i + 2 > n) break;
        amin(ans[i], ans[i + 2] - 1);
        amax(ans[i], 0);
    }
    rep(i, 1, n + 1) {
        amin(ans[i], ans[i - 1] + 1);
    }
    rrep(i, n, 1) {
        amin(ans[i - 1], ans[i]);
    }
    re ans;
}

vi solve2() {
    vector<event> e;
    rep(i, 0, n) {
        auto [l, r] = segs[i];
        e.pb({l, 1, i});
        e.pb({r, -1, i});
    }
    sort(all(e), [&](auto a, auto b) {
        re a.x < b.x || (a.x == b.x && a.type > b.type) || (a.x == b.x && a.type == b.type && a.idx < b.idx);
    });
    vi left, right;
    for (auto [l, r] : segs) {
        left.pb(l);
        right.pb(r);
    }
    sort(all(left));
    sort(all(right));
    vi cnts(n), ans(n + 1, INF);
    int cnt = 0;
    for (auto [x, type, idx] : e) {
        cnt += type;
        int ll = lower_bound(all(right), x) - right.begin();
        int rr = upper_bound(all(left), x) - left.begin();
        rr = left.size() - rr;
        amin(ans[cnt], 0);
        int tmp_cnt = cnt, cur_ns = 0;
        while (ll > 0 && rr > 0) {
            tmp_cnt += 2;
            ll--, rr--;
            cur_ns++;
            amin(ans[tmp_cnt], cur_ns);
        }
        while (ll > 0 || rr > 0) {
            ll = ll - 1;
            rr = rr - 1;
            amax(ll, 0);
            amax(rr, 0);
            tmp_cnt++;
            cur_ns++;
            amin(ans[tmp_cnt], cur_ns);
        }
    }
    rrep(i, n, 1) {
        amin(ans[i - 1], ans[i]);
    }
    re ans;
}

random_device rd;
mt19937 rnd(rd());

void solve() {
    cin >> n >> q;
    segs.resize(n);
    for (auto& [l, r] : segs) {
        cin >> l >> r;
    }
    vi ans = solve1();
    while (q--) {
        int pos; cin >> pos;
        cout << ans[pos] << " ";
    }
    cout << "\n";
    /*n = rnd() % 7 + 1;
    segs.resize(n);
    set<int> ss;
    while (ss.size() < 2 * n) {
        ss.insert(rnd() % 20 + 1);
    }
    vi vec;
    for (int x : ss) {
        vec.pb(x);
    }
    for (auto& [l, r] : segs) {
        int right = rnd() % (int)vec.size() + 1;
        if (right == vec.size()) {
            right--;
        }
        int left = rnd() % right;
        l = vec[left];
        r = vec[right];
        vec.erase(vec.begin() + right);
        vec.erase(vec.begin() + left);
    }
    if (solve1() != solve2()) {
        cout << n << "\n";
        for (auto [l, r] : segs) {
            cout << l << " " << r << "\n";
        }
        for (int x : solve1()) {
            cout << x << " ";
        }
        cout << "\n";
        for (int x : solve2()) {
            cout << x << " ";
        }
        cout << "\n";
        exit(0);
    }*/
}