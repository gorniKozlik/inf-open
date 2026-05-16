#include <bits/stdc++.h>

using namespace std;

struct Event {
    int cord;
    int t;
    int ind;
};

bool comp(Event &a, Event &b) {
    if (a.cord == b.cord) {
        return a.t < b.t;
    }
    return a.cord < b.cord;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> qq(q);
    for (int i = 0; i < q; i++) {
        cin >> qq[i];
    }
    vector<int> ans(n + 1);
    sort(a.begin(), a.end());
    int j = 0;
    vector<Event> e;
    for (int i = 0; i < n; i++) {
        e.push_back({a[i].first, -1, i});
        e.push_back({a[i].second, 1, i});
    }
    sort(e.begin(), e.end(), comp);
    int cnt = 0;
    int cur = 0;
    for (auto to : e) {
        if (to.t == -1) {
            cur++;
        } else {
            cur--;
        }
        cnt = max(cur, cnt);
    }
    // cerr << cnt << endl;
    j = cnt + 1;
    for (int i = 0; i < n; i++) {
        int l = a[i].first, r = a[i].second;
        int ql = l, qr = r;
        int ind = -1;
        for (int jj = i + 1; jj < n; jj++) {
            if (a[jj].first > ql || (a[jj].first == ql && a[jj].second > qr)) {
                ind = jj;
                ql = a[jj].first;
                qr = a[jj].second;
            }
        }
        if (r < ql) {
            for (auto &[cord, t, jj] : e) {
                if (t == 1 && jj == i) {
                    cord = qr;
                }
                if (t == -1 && jj == ind) {
                    cord = r;
                }
            }
            sort(e.begin(), e.end(), comp);
            cnt = 0;
            cur = 0;
            for (auto to : e) {
                if (to.t == -1) {
                    cur++;
                } else {
                    cur--;
                }
                cnt = max(cur, cnt);
            }
            int la = ans[j - 1] + 1;
            while (j <= cnt) {
                ans[j] = la;
                j++;
            }
        }
    }
    for (auto to : qq) {
        cout << ans[to] << " ";
    }
    cout << endl;
}
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}