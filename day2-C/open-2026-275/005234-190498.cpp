#include <iostream>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair <int, int>;
template <typename T>
using vec = vector <T>;

/*
template <typename T>
istream& operator >>(istream& in, vec <T>& a) {
    for (auto& x : a) {
        in >> x;
    }
    return in;
}*/
template <typename T>
ostream& operator <<(ostream& in, vec <T>& a) {
    for (T& x : a) in << x << " ";
    return in;
}
template <typename T, typename Y>
istream& operator >>(istream& in, pair <T, Y>& a) {
    in >> a.first >> a.second;
    return in;
}
template <typename T, typename Y>
ostream& operator <<(ostream& in, pair <T, Y>& a) {
    in << a.first << " " << a.second;
    return in;
}

//#define int long long

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, q;
    cin >> n >> q;

    vec <pii> a(n);
    for (auto& x : a) cin >> x.first >> x.second;

    vec <int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[i] = i / 2;
    }
    /*if (n % 2 == 0) {
        for (int i = 2; i <= n; i++) {
            ans[i] = i / 2;
        }
    }
    else {
        for (int i = 2; i <= n; i++) {
            ans[i] = i / 2;
        }
    }*/

    while (q--) {
        int p;
        cin >> p;
        cout << ans[p] << "\n";
    }
}
