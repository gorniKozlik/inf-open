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
    vector<Event> e;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        e.push_back({l, -1, i});
        e.push_back({r, 1, i});
    }
    vector<int> qq(q);
    for (int i = 0; i < q; i++) {
        cin >> qq[i];
    }
    sort(e.begin(), e.end(), comp);
    int cnt = 0;
    int cur = 0;
    vector<int> ans(n + 10);
    for (auto to : e) {
        if (to.t == -1) {
            cur++;
        } else {
            cur--;
        }
        cnt = max(cnt, cur);
    }
    int j = cnt + 1;
    int open = n, close = 0;
    int k = 0;
    cur = 0;
    for (auto to : e) {
        if (to.t == -1) {
            cur++;
            open--;
        } else {
            cur--;
            close++;
        }
        k = max(k, min(open, close));
    }
    while (k > 0) {
        ans[j + 1] = ans[j] = ans[j - 1] + 1;
        j += 2;
        k--;
    }
    for (int i = j; i <= n; i++) {
        ans[i] = ans[i - 1] + 1;
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