#include <bits/stdc++.h>

using namespace std;
#define int long long

void bad() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector <int> l(n), r(n);
    vector <int> p;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        p.push_back(l[i]);
        p.push_back(r[i]);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    sort(p.begin(), p.end());
    vector <int> ans(n + 1, 2e9);
    int ind1 = 0, ind2 = 0;
    int counter = 0;
    vector <vector <int>> a(n + 1), d(n + 1);
    for (int i = 0; i < 2 * n; ++i) {
        bool flag = false;
        while (ind1 < n && l[ind1] <= p[i]) {
            ++counter;
            ++ind1;
            flag = true;
        }
        ans[counter] = 0;
        int v1 = ind2;
        int v2 = n - ind1;
        if (min(v1, v2) != 0) {
            a[counter + 1].push_back(counter);
            d[counter + 2 * min(v1, v2)].push_back(counter);
        }
        if (v1 > v2 && flag) {
            ans[counter + 2 * v2 + 1] = min(ans[counter + 2 * v2 + 1], v2 + 1);

        }
        if (v2 > v1 && flag == false) {
            ans[counter + 2 * v1 + 1] = min(ans[counter + 2 * v1 + 1], v1 + 1);
        }
        while (ind2 < n && r[ind2] <= p[i]) {
            --counter;
            ++ind2;
        }
    }
    multiset <int> now;
    for (int i = 0; i <= n; ++i) {
        for (int v : a[i]) {
            now.insert(v);
        }
        if (!now.empty()) {
            int v = *now.rbegin();
            ans[i] = min(ans[i], (i - v + 1) / 2);
        }
        for (int v : d[i]) {
            now.erase(now.find(v));
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        cout << ans[t] << ' ';
    }
    cout << '\n';
}
signed main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    bad();
}
