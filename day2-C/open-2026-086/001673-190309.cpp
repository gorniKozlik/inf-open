#include <iostream>
#include <bits/stdc++.h>
#include <random>
using namespace std;

long long inf = 1e17;

// random_device rd;
// mt19937 rnd(rd);
// uniform_int_distribution<> gen(0, 5);

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> res(n + 1, n + 1);
    vector<int> l(n);
    map<int, int> r;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        l[i] = x;
        r[x] = y;
    }
    sort(l.begin(), l.end());
    for (int i = 0; i < n; i++) {
        set<int> s1, s2;
        for (int k = 0; k < 10; k++) {
            s1.insert(l[i + k]);
            s2.insert(r[l[i + k]]);
            int cnt = 0;
            auto it1 = s1.end();
            it1--;
            auto it2 = s2.begin();
            while (*it1 > *it2) {
                cnt++;
                it1--;
                it2++;
            }
            res[k + 1] = min(res[k + 1], cnt);
        }
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << res[k] << '\n';
    }
}