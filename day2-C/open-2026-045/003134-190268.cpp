#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cassert>
#include <random>
#define rep(n) for (int (i) = 0; (i) < (n); (i)++)
#define all(n) (n).begin(), (n).end()
#define rall(n) (n).rbegin(), (n).rend()
#define mp make_pair
#define ll long long
#define ld long double
//#define int long long
//#define FILE
//#define DEBUG

using namespace std;

struct segtree {
    struct node {
        node *l=nullptr, *r=nullptr;
        int mx=0, p=0;
    };
    
    node* root = new node();

    void expand(node *v) {
        if (v->l == nullptr)
            v->l = new node();
        if (v->r == nullptr)
            v->r = new node();
    }

    void apply(node *v, int val) {
        v->mx += val;
        v->p += val;
    }

    void push(node *v) {
        apply(v->l, v->p);
        apply(v->r, v->p);
        v->p = 0;
    }

    void upd(node *v, int l, int r, int L, int R, int val) {
        if (r <= L || R <= l)
            return;
        if (L <= l && r <= R) {
            apply(v, val);
            return;
        }
        expand(v);
        push(v);
        int m = (l + r) / 2;
        upd(v->l, l, m, L, R, val);
        upd(v->r, m, r, L, R, val);
        v->mx = max(v->l->mx, v->r->mx);
    }

    int get(node *v, int l, int r, int L, int R) {
        if (r <= L || R <= l)
            return 0;
        if (L <= l && r <= R) {
            return v->mx;
        }
        expand(v);
        push(v);
        int m = (l + r) / 2;
        return max(get(v->l, l, m, L, R), get(v->r, m, r, L, R));
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> A(n);
    rep(n) cin >> A[i].first >> A[i].second;
    vector<int> Q(q);
    rep(q) cin >> Q[i];

    vector<int> P;
    rep(n) {
        P.push_back(A[i].first);
        P.push_back(A[i].second);
    }
    sort(all(P));
    int sz = n * 2 - 1;
    segtree tree;
    for (auto [a, b] : A) {
        int l = lower_bound(all(P), a) - P.begin();
        int r = lower_bound(all(P), b) - P.begin();
        tree.upd(tree.root, 0, sz, l, r, 1);
    }
    sort(all(P));
    rep(q) {
        int k = Q[i];
        int cnt = tree.get(tree.root, 0, sz, k - 1, sz - k + 1);
        int ans = (max<int>(0, k - cnt) + 1) / 2;
        cout << ans << '\n';
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
#ifdef FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "W", stdout);
#endif
#ifndef DEBUG
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
#else

#endif
}