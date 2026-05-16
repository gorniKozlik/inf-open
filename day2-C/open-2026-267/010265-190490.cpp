#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,lzcnt,popcnt,bmi,bmi2")
using namespace std;


struct Node {
    int l, r, x, pd;
    Node *left = 0, *right = 0;
};

void update(Node *v) {
    v->x = 0;
    if (v->left) v->x = max(v->x, v->left->x);
    if (v->right) v->x = max(v->x, v->right->x);
}

void push_down(Node *v) {
    if (v->left) {
        v->left->x += v->pd;
        v->left->pd += v->pd;
    }
    if (v->right) {
        v->right->x += v->pd;
        v->right->pd += v->pd;
    }
    v->pd = 0;
}

void ad(Node *v, int ql, int qr, int val, bool first) {
    if (ql > qr) return;
    if (v->l > qr || ql > v->r) return;
    if (ql <= v->l && v->r <= qr) {
        if (first) {
            if (ql == v->l && qr == v->r) {
                ad(v, ql, ql, 1, false);
                ad(v, qr, qr, 1, false);
                ad(v, ql + 1, qr - 1, 2, false);
            }
            else if (ql == v->l) {
                ad(v, ql, ql, 1, false);
                ad(v, ql + 1, qr, 2, false);
            }
            else if (qr == v->r) {
                ad(v, qr, qr, 1, false);
                ad(v, ql, qr - 1, 2, false);
            }
            else ad(v, ql, qr, val, false);
            return;
        }
        // cout << v->x << " ";
        v->x += val;
        v->pd += val;
        // cout << v->l << " " << v->r << " " << v->x << endl;
        return;
    }
    int m = (v->l + v->r) / 2;
    if (!v->left) {
        v->left = new Node{v->l, m, 0, 0, 0, 0};
    }
    if (!v->right) {
        v->right = new Node{m + 1, v->r, 0, 0, 0, 0};
    }
    push_down(v);
    ad(v->left, ql, qr, val, first);
    ad(v->right, ql, qr, val, first);
    update(v);
    // cout << v->l << " "  << v->r << " " << v->x << " " << endl;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;
    Node *p = new Node{0, 1000000005, 0, 0, 0, 0};
    vector<pair<int, int>> line;
    for (int i = 0; i < n; i++) {
        // cout << "!!!!";
        // ad(p, 12, 14, 0);
        int l, r; cin >> l >> r;
        ad(p, l, r, 1, false);
        line.emplace_back(l, 1);
        line.emplace_back(r, -1);
    }
    sort(line.begin(), line.end());

    // ad(p, 12, 14, 0);
    int ans = p->x;
    int l = 0, r = line.size() - 1;
    int cnt = 0;
    vector<int> anss(n + 1, 0);
    while (ans < n) {
        while (line[l].second != -1) l++;
        while (line[r].second != 1) r--;
        ad(p, line[l].first, line[r].first, 2, true);
        // ad(p, line[l].first, line[l].first, 1);
        // ad(p, line[r].first, line[r].first, 1);
        for (int i = ans + 1; i <= p->x; i++) anss[i] = cnt + 1;
        ans = p->x;
        cnt++;
        // cout << line[l].first << "! " << line[r].first << " " << ans << " " << cnt << endl;
        l++, r--;
    }
    for (int qr = 0; qr < q; qr++) {
        int ind; cin >> ind; cout << anss[ind] << " ";
    }

    return 0;
}