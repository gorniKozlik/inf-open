#include <bits/stdc++.h>

using namespace std;

struct node {
    int mx, mod;
};

vector<node> tree;

void push(int v, int l, int r) {
    if(tree[v].mod == 0) return;
    tree[v * 2 + 1].mod += tree[v].mod;
    tree[v * 2 + 2].mod += tree[v].mod;
    tree[v * 2 + 1].mx += tree[v].mod;
    tree[v * 2 + 2].mx += tree[v].mod;
    tree[v].mod = 0;
}

void addSeg(int v, int l, int r, int ql, int qr, int x) {
    if(l >= qr || r <= ql) return;
    if(l >= ql && r <= qr) {
        tree[v].mod += x;
        tree[v].mx += x;
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    addSeg(v * 2 + 1, l, m, ql, qr, x);
    addSeg(v * 2 + 2, m, r, ql, qr, x);
    tree[v].mx = max(tree[v * 2 + 1].mx, tree[v * 2 + 2].mx);
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> evs;
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        evs.push_back({l, 1});
        evs.push_back({r, -1});
    }
    sort(evs.begin(), evs.end());
    string psp;
    for(auto [x, t] : evs) {
        if(t == 1) psp.push_back('(');
        else psp.push_back(')');
    }
    set<int> idxOpen, idxClose;
    for(int i = 0; i < psp.size(); i++) {
        if(psp[i] == '(') idxOpen.insert(i);
        else idxClose.insert(i);
    }
    int sz = psp.size();
    tree.resize(sz * 4);
    for(int i = 0; i < sz; i++) {
        if(psp[i] == '(') addSeg(0, 0, sz, i, sz, 1);
        else addSeg(0, 0, sz, i, sz, -1);
    }
    int cur = 0;
    vector<int> anss(n + 1);
    int ops = 0;
    while(true) {
        int mxbal = tree[0].mx;
        while(cur < mxbal) anss[cur++] = ops;
        int aa = *idxClose.begin();
        int bb = *idxOpen.rbegin();
        if(aa > bb) break;
        idxClose.erase(aa);
        idxOpen.erase(bb);
        idxOpen.insert(aa);
        idxClose.insert(bb);
        addSeg(0, 0, sz, aa, sz, 2);
        addSeg(0, 0, sz, bb, sz, -2);
        // swap(psp[aa], psp[bb]);
        ops++;
    }
    while(q--) {
        int xx;
        cin >> xx;
        cout << anss[xx - 1] << ' ';
    }
    cout << '\n';
}
