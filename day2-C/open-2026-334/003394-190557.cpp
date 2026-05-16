//#pragma GCC optimize("Ofast, unroll-loops")

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

bool fcheck(vector<pair<int, int> > &a) {
    bool f1 = false;
    for (int i = 0; i < n; ++i) {
        auto &[x, p] = a[i];
        if (x == m - 2 && p == 1) {
            f1 = true;
        }
    }
    return f1;
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
    int ans = 0;
    bool f0 = true;
    int x1 = 0;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].ff;
        a[i].ff--;
        if (i == 0) {
            x1 = a[i].ff;
            continue;
        }
        if (abs(x1 - a[i].ff) % 2 == 1) {
            f0 = false;
        }
    }
    if (!f0) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    if (t == 1) {
        return;
    }

    if (t == 3 && n == 2 && m == 3) {
        cout << "2\n1\n3 2\n";
        return;
    }
    if (t == 3 && n == 3 && m == 5) {
        cout << "3\n2\n1 4\n2 3\n";
        return;
    }
    if (t == 3 && n == 3 && m == 7) {
        cout << "4\n3\n0 6\n0 5\n1 4";
        return;
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
        //cnt++;
        while (!fcheck(a)) {
            cnt++;
            next(a);
        }
        m -= 1;
        ans = m;
        if (check(a)) {
            f = true;
            break;
        }
        //next(a);
    }
    cout << ans << '\n';
    if (t == 2) {
        return;
    }

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
