#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,lzcnt,popcnt,bmi,bmi2")
using namespace std;


struct Node {
    int x, pd;
};
const int maxn = 400005;
Node tree[4 * maxn];

void update(int v) {
    tree[v].x = max(tree[2 * v + 1].x, tree[2 * v + 2].x);
}

void push_down(int v) {
    tree[2 * v + 1].x += tree[v].pd;
    tree[2 * v + 1].pd += tree[v].pd;
    tree[2 * v + 2].x += tree[v].pd;
    tree[2 * v + 2].pd += tree[v].pd;
    tree[v].pd = 0;
}

void ad(int v, int l, int r, int ql, int qr, int val, bool first) {
    if (ql > qr) return;
    if (l > qr || ql > r) return;
    if (ql <= l && r <= qr) {
        if (first) {
            if (ql == l && qr == r) {
                ad(v, l, r, ql, ql, 1, false);
                ad(v, l, r, qr, qr, 1, false);
                ad(v, l, r, ql + 1, qr - 1, 2, false);
            }
            else if (ql == l) {
                ad(v, l, r, ql, ql, 1, false);
                ad(v, l, r, ql + 1, qr, 2, false);
            }
            else if (qr == r) {
                ad(v, l, r, qr, qr, 1, false);
                ad(v, l, r, ql, qr - 1, 2, false);
            }
            else ad(v, l, r, ql, qr, val, false);
            return;
        }
        // cout << tree[v].x << " ";
        tree[v].x += val;
        tree[v].pd += val;
        // cout << l << " " << r << " " << tree[v].x << endl;
        return;
    }
    int m = (l + r) / 2;
    push_down(v);
    ad(2 * v + 1, l, m, ql, qr, val, first);
    ad(2 * v + 2, m + 1, r, ql, qr, val, first);
    update(v);
    // cout << l << " "  << r << " " << tree[v].x << " " << endl;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;

    set<int> comp;
    vector<pair<int, int>> inp(n);
    for (int i = 0; i < n; i++) {cin >> inp[i].first >> inp[i].second; comp.insert(inp[i].first); comp.insert(inp[i].second);}
    int cc = 0;
    unordered_map<int, int> tocomp;
    for (auto i : comp) {
        tocomp[i] = cc++;
    }
    for (int i = 0; i < n; i++) {
        inp[i].first = tocomp[inp[i].first];
        inp[i].second = tocomp[inp[i].second];
    }
    int nn = comp.size();
    vector<pair<int, int>> line;
    for (int i = 0; i < n; i++) {
        // cout << "!!!!";
        // ad(p, 12, 14, 0);
        auto [l, r] = inp[i];
        ad(0, 0, nn - 1, l, r, 1, false);
        line.emplace_back(l, 1);
        line.emplace_back(r, -1);
    }
    sort(line.begin(), line.end());

    // ad(p, 12, 14, 0);
    int ans = tree[0].x;
    int l = 0, r = line.size() - 1;
    int cnt = 0;
    vector<int> anss(n + 1, 0);
    while (ans < n) {
        while (line[l].second != -1) l++;
        while (line[r].second != 1) r--;
        ad(0, 0, nn - 1, line[l].first, line[r].first, 2, true);
        // ad(p, line[l].first, line[l].first, 1);
        // ad(p, line[r].first, line[r].first, 1);
        for (int i = ans + 1; i <= tree[0].x; i++) anss[i] = cnt + 1;
        ans = tree[0].x;
        cnt++;
        // cout << line[l].first << "! " << line[r].first << " " << ans << " " << cnt << endl;
        l++, r--;
    }
    for (int qr = 0; qr < q; qr++) {
        int ind; cin >> ind; cout << anss[ind] << " ";
    }

    return 0;
}