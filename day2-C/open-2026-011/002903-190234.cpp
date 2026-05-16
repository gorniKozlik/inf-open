#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #pragma GCC optimize("O3,Ofast,unroll-loops")
// #pragma GCC target("avx2,bmi")

using namespace std;
// using namespace __gnu_pbds;
// template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    int t = 1;
    while (t--) {
        solve();
    }
}

#define int long long
const int MAXN = 1e6 + 1, MOD = 998244353, INF = 2e18;

struct P {
    int x, y, ind;
};

bool comp(P a, P b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

void solve() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<P> vec;
    vector<pair<int,int> > a;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        vec.push_back({l, 0, i});
        vec.push_back({r, 1, i});
        a.push_back({l, r});
    }
    sort(vec.begin(), vec.end(), comp);
    int now = 0;
    int mx = 0, ind = 0;
    int l1 = -INF, r1 = INF;
    int l = 0, r = n;
    vector<int> beb(n + 1, INF);
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].y == 0) {
            now++;
            r--;
            beb[now + min(l,r) * 2] = min(beb[now+min(l,r) * 2], min(l,r));
            beb[now] = min(beb[now], (int)0);
            if (now > mx) {
                mx = now;
                ind = i;
                l1 = l, r1 = r;
            } else if (now == mx) {
                if (abs(r-l) < abs(r1-l1)) {
                    l1 = l, r1 = r;
                }
            }
        } else {
            now--;
            l++;
            beb[now + min(l,r) * 2] = min(beb[now+min(l,r) * 2], min(l,r));
        }
    }

    for (int i = n-1; i >= 1; i--) {
        if (beb[i + 1] != INF) {
            beb[i] = min(beb[i], beb[i + 1]);
        }
        if (i < n-2 && beb[i + 2] != INF&&beb[i + 2] != 0) {
            beb[i] = min(beb[i], beb[i + 2] - 1);
        }
    }
    vector<int> cnt(n + 1);
    int mn = INF;
    for (int i = 2; i <= n; i++) {
        beb[i] = min(beb[i], beb[i-1] + 1);
    }
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << beb[x] << ' ';
    }
    return;
    // vector<pair<int,int> > qq(q);
    // for (int i = 0; i < q; i++) {
    //     cin >> qq[i].first;
    //     qq[i].second = i;
    // }
    // sort(qq.begin(), qq.end());
    // vector<int> ans(q);
    // now = 0;
    // while (now < q && qq[now].first <= mx) {
    //     ans[qq[now].second] = 0;
    //     now++;
    // }
    // int cnt = 0;
    // while (now < q) {
    //     while (mx < qq[now].first) {
    //         if (l1 && r1) {
    //             l1--;r1--;
    //             mx += 2;
    //         } else {
    //             mx++;
    //         }
    //         cnt++;
    //     }
    //     ans[qq[now].second] = cnt;
    //     now++;
    // }
    // for (int i: ans) {
    //     cout << i << ' ';
    // }
}
