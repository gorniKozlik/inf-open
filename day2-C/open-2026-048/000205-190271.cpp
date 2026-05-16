#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> a(n);
    vector<int> sor(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        sor[2 * i] = a[i].first;
        sor[2 * i + 1] = a[i].second;
    }
    sort(sor.begin(), sor.end());
    for (auto &[l, r] : a) {
        l = lower_bound(sor.begin(), sor.end(), l) - sor.begin();
        r = lower_bound(sor.begin(), sor.end(), r) - sor.begin();
    }
    vector<int> ans(n + 1, 1000000000);
    vector<int> cn(2 * n);
    vector<pair<int, int>> evs;
    for (int i = 0; i < n; ++i) {
        evs.emplace_back(a[i].first, -1);
        evs.emplace_back(a[i].second, 1);
        evs.emplace_back(i, 0);
        evs.emplace_back(i + n, 0);
    }
    sort(evs.begin(), evs.end());
    int cur = 0;
    for (auto [tm, tp] : evs) {
        if (tp == 0) {
            cn[tm] = cur;
        } else {
            cur -= tp;
        }
    }
    int alr = *max_element(cn.begin(), cn.end());
    for (int i = 0; i <= alr; ++i) {
        ans[i] = 0;
    }
    int ops = 0;
    while (alr != n) {
        ops++;
        int minR = 1000000000, i1 = -1;
        int maxL = -1000000000, i2 = -1;
        for (int i = 0; i < n; ++i) {
            auto [l, r] = a[i];
            if (r < minR) {
                minR = r;
                i1 = i;
            }
            if (l > maxL) {
                maxL = l;
                i2 = i;
            }
        }
        if (i1 == i2) {
            assert(false);
        }
        assert(minR < maxL);
        for (int j = minR + 1; j < maxL; ++j) {
            cn[j] += 2;
        }
        cn[minR]++;
        cn[maxL]++;
        a[i1].second = maxL;
        a[i2].first = minR;
        int newAlr = *max_element(cn.begin(), cn.end());
        for (int j = alr + 1; j <= newAlr; ++j) {
            ans[j] = ops;
        }
        alr = newAlr;
    }
    for (int t = 0; t < q; ++t) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    cout << "\n";
}
