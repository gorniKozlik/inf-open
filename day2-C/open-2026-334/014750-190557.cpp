//#pragma GCC optimize("Ofast, unroll-loops")

#include <bits/stdc++.h>
//#include<iostream>


using namespace std;
using ll = long long;
using sll = __int128_t;
int n, q;

void solve() {
    cin >> n >> q;
    vector<int> lt(n), rt(n);
    vector<pair<int, int> > points;
    vector<pair<int, int> > pointsr;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        lt[i] = x;
        rt[i] = y;
        points.emplace_back(x, 1);
        points.emplace_back(y, -1);
        pointsr.emplace_back(-x, -1);
        pointsr.emplace_back(-y, 1);
    }
    sort(points.begin(), points.end());
    sort(pointsr.begin(), pointsr.end());
    int cnt = 0;
    int cx = 2e9;
    int opened = 0, closed = 0;
    vector<int> ans(n + 1, 2e9);
    for (auto [x, st]: points) {
        cnt++;
        if (st == -1) {
            opened++;
        }
        if (cnt == n) {
            cx = x;
            break;
        }
        if (st == 1) {
            closed++;
        }
    }
    ans[n] = n - opened;
    int bal = 0;
    int mx = 0;
    cnt = 0;
    opened = 0;
    vector<array<int, 4> > prevmx;
    for (int i = n - 1; i >= 0; --i) {
        auto [x, st] = points[i];
        bal -= st;
        cnt++;
        if (st == -1) {
            opened++;
        }
        if (bal > mx) {
            mx = bal;
            prevmx.push_back({mx, x, i, opened});
        }
        if (st == 1) {
            closed++;
        }
    }

    int pr = mx + 1;
    int m = prevmx.size();
    reverse(prevmx.begin(), prevmx.end());
    for (int i = 0; i < pr; ++i) {
        ans[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        auto [cmx, cx, ci, cop] = prevmx[i];
        //for (int j = cmx + 1; j <= n - cop; ++j) {
        for (int j = pr; j <= n - cop; ++j) {
            ans[j] = min(ans[j], (j - cmx + 1) / 2);
        }
        pr = n - cop + 1;
    }





    bal = 0;
    mx = 0;
    prevmx.clear();
    cnt = 0;
    opened = 0;
    for (int i = n - 1; i >= 0; --i) {
        auto [x, st] = pointsr[i];
        bal -= st;
        cnt++;
        if (st == -1) {
            opened++;
        }
        if (bal > mx) {
            mx = bal;
            prevmx.push_back({mx, x, i, opened});
        }
        if (st == 1) {
            closed++;
        }
    }

    pr = mx + 1;
    m = prevmx.size();
    reverse(prevmx.begin(), prevmx.end());
    for (int i = 0; i < pr; ++i) {
        ans[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        auto [cmx, cx, ci, cop] = prevmx[i];
        //for (int j = cmx + 1; j <= n - cop; ++j) {
        for (int j = pr; j <= n - cop; ++j) {
            ans[j] = min(ans[j], (j - cmx + 1) / 2);
        }
        pr = n - cop + 1;
    }

    //int m = prevmx.size();
    //ответ для всех k <= mx = 1 дальше для всех от mx до количества mx + min(слева закрыто или справа не открыто) просто по +1 на каждые два
    //далее мы получается прыгаем на следующий меньший максимум находящийся ближе к n == cnt
    //n - opened

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //cin >> t;
#endif
    while (t--) {
        solve();
    }
    return 0;
}
