#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define int long long

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

const int N = (1 << 20);
const int K = (1 << 19);
int tree[N];
int must[N];

void update(int v, int tl, int tr, int l, int r, int x) {
    if (tr <= l || r <= tl) return;
    if (l <= tl && tr <= r) {
        must[v] += x;
        return;
    }

    must[v * 2] += must[v];
    must[v * 2 + 1] += must[v];
    must[v] = 0;

    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, r, x);
    update(v * 2 + 1, tm, tr, l, r, x);
    tree[v] = max(tree[v * 2] + must[v * 2], tree[v * 2 + 1] + must[v * 2 + 1]);
}

int get(int v, int tl, int tr, int l, int r) {
    if (tr <= l || r <= tl) return 0;
    if (l <= tl && tr <= r) {
        return tree[v] + must[v];
    }
    must[v * 2] += must[v];
    must[v * 2 + 1] += must[v];
    must[v] = 0;

    int tm = (tl + tr) / 2;
    return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
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

    int opened = 0;
    for (int v = K; v < K + s.size(); v++) {
        if (s[v - K] == '(') {
            opened++;
        } else {
            opened--;
        }
        tree[v] = opened;
    }
    for (int v = K - 1; v > 0; v--) {
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    int k = get(1, 1, K, 1, s.size() + 1);
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

        update(1, 1, K, l, r, 2);

        int new_k = get(1, 1, K, 1, s.size() + 1);
        for (int i = k + 1; i <= new_k; i++) ans[i] = t;
        k = new_k;
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
}
