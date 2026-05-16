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
    vector<array<int, 3>> answers;
    for (int x : xs) {
        bal += start[x];
        int flag = 0;
        int right = n - left - bal;
        if (start[x] == 1 && left > right) flag = 1;
        if (fin[x] == 1 && right > left) flag = 1;
        answers.push_back({bal, bal + min(left, right) * 2, flag});
        // cout << x << ": " << bal << "\n";
        // cout << x << ": " << answers.back()[0] << " " << answers.back()[1] << "\n";
        left += fin[x];
        bal -= fin[x];
    }
    while (q--) {
        int k;
        cin >> k;
        int ans = n;
        for (auto [a, b, c] : answers) {
            if (k <= a) {
                ans = 0;
            } else if (k <= b) {
                ans = min(ans, (k + 1 - a) / 2);
            } else if (k <= b + c) {
                ans = min(ans, (b - a) / 2 + 1);
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}