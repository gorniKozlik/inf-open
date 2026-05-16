#pragma GCC optimize("Ofast, unroll-loops")

#include <bits/stdc++.h>
//#include<iostream>


using namespace std;
using ll = long long;
using sll = __int128_t;
#define ff first
#define ss second
int n, m, t;

void next(vector<pair<int, int> > &a) {
    for (int i = 0; i < n; ++i) {
        auto &[x, p] = a[i];
        x += p;
        if (x == m - 1 && p == 1 || x == 0 && p == -1) {
            p *= -1;
        }
    }
}

bool check(vector<pair<int, int> > &a) {
    for (int i = 0; i < n; ++i) {
        auto &[x, p] = a[i];
        if (x == m - 1 && p == 1 || x == 0 && p == -1) {
            p *= -1;
        }
    }
    auto f1 = a[0];
    for (int i = 0; i < n; ++i) {
        if (f1 != a[i]) {
            return false;
        }
    }
    return true;
}

pair<int, int> mxfun(vector<pair<int, int> > &a) {
    int mx = a[0].ff, mxi = 0;
    for (int i = 0; i < n; ++i) {
        if (mx < a[i].ff) {
            mx = a[i].ff;
            mxi = i;
        }
    }
    return make_pair(mx, mxi);
}


void solve() {
    cin >> t >> n >> m;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].ff;
        a[i].ff--;
    }
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == 'R') {
            a[i].ss = 1;
        } else {
            a[i].ss = -1;
        }
    }
    bool f = false;
    int cnt = 0;
    while (cnt < 10000) {
        cnt++;
        auto [mx, mxi] = mxfun(a);
        m = mx + 1;
        if (check(a)) {
            f = true;
            break;
        }
        next(a);
    }
    if (f) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //!!!!!!!!!!!!!
    //!!!!!!!!!!!!!
    //t = 6;
#endif
    while (t--) {
        solve();
    }
    return 0;
}
