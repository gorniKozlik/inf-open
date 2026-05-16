#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

struct Kol {
    int x;
    char skobka;

    bool operator<(const Kol &other) const {
        return x < other.x;
    }
};

int check(string s) {
    int opened = 0;
    int ans = 0;
    for (char c: s) {
        if (c == '(') {
            opened++;
            ans = max(opened, ans);
        } else {
            opened--;
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Kol> skobki;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        skobki.push_back({l, '('});
        skobki.push_back({r, ')'});
    }
    sort(skobki.begin(), skobki.end());
    string s;
    for (auto el: skobki) s.push_back(el.skobka);
    int k = check(s);
    vector<int> ans(n + 1, 0);
    int l = 0;
    int r = s.size() - 1;
    int t = 0;
    while (l <= r && k < n) {
        t++;
        while (s[l] != ')') l++;
        while (s[r] != '(') r--;
        if (l > r) {
            ans[n] = t - 1;
            break;
        }
        s[l] = '(';
        s[r] = ')';
        // int new_k = check(s);
        // for (int i = k + 1; i <= new_k; i++) ans[i] = t;
        // k = new_k;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
}
