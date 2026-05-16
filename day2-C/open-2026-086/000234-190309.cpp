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
    int n, q, res = 0;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x > n) {
            res++;
        }
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << res / 2 << '\n';
    }
}