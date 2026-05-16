#include <bits/stdc++.h>

using namespace std;

signed main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<array<int, 2>> segs(n);
    for (auto& [l, r] : segs) cin >> l >> r;
    vector<int> xs;
    unordered_map<int, int> start, fin;
    for (auto& [l, r] : segs) {
        xs.push_back(l);
        xs.push_back(r);
        start[l]++;
        fin[r]++;
    }
    sort(xs.begin(), xs.end());
    int bal = 0, left = 0;
    deque<array<int, 3>> answers;
    int maxl = 0;
    for (int x : xs) {
        bal += start[x];
        int flag = 0;
        int right = n - left - bal;
        if (start[x] == 1 && left > right) flag = 1;
        if (fin[x] == 1 && right > left) flag = 1;
        answers.push_back({bal, bal + min(left, right) * 2, flag});
        maxl = max(maxl, bal);
        left += fin[x];
        bal -= fin[x];
    }
    sort(answers.begin(), answers.end());
    vector<array<int, 3>> st;
    vector<int> ans(n + 1, n + 1);
    for (int i = 0; i <= maxl; i++) {
        ans[i] = 0;
    }
    for (int i = maxl + 1; i <= n; i++) {
        while (st.size() && st.back()[1] < i) {
            st.pop_back();
        }
        while (answers.size() && answers.front()[0] <= i) {
            st.push_back(answers.front());
            answers.pop_front();
            auto [a, b, c] = st.back();
            if (c == 1) {
                ans[b + 1] = min(ans[b + 1], (b - a) / 2 + 1);
            }
        }
        if (st.size()) {
            auto [a, b, c] = st.back();
            ans[i] = min(ans[i], (i + 1 - a) / 2);
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    cout << "\n";
}