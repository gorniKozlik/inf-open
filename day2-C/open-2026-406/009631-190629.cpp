#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define int long long

struct hz {
    int xmax = 0;
    int xinter = 0;
    int b2 = 0;
    int b1 = 0;
};

bool cmp(hz a, hz b) {
    if (a.xmax == b.xmax) {
        if (a.xinter == b.xinter) {
            return a.b2 > b.b2;
        }
        return a.xinter < b.xinter;
    }
    return a.xmax < b.xmax;
}

struct seg {
    int y1, y2, k, b;
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > line;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        line.emplace_back(l, 1);
        line.emplace_back(r, 2);
    }
    sort(line.begin(), line.end());
    int cntl = 0;
    int cntr = 0;
    int lastpos = 0;
    map<int,int> endr;
    int x = 0;
    vector<hz> v;
    int cnt = 0;
    for (auto [pos,id]: line) {
        if (id == 1) {
            cntl++;
            endr[pos] = cntr;
            cnt++;
        }
        int alr = cnt;
        int s = min(n - cntl, endr[lastpos]);
        v.emplace_back(n - s * 2 - alr + s, s, alr,
                       s * 2 + alr - s);

        if (id == 2) {
            endr[pos] = cntr;
            cntr++;
            cnt--;
        }

        lastpos = pos;
    }
    sort(v.begin(), v.end(), cmp);
    vector<seg> conv;
    conv.emplace_back(n, v[0].xinter * 2 + v[0].b2, 1, n - v[0].xmax);
    int lasty = v[0].xinter * 2 + v[0].b2;
    hz prev = v[0];
    for (int i = 1; i < v.size(); ++i) {
        auto nw = v[i];
        int xn = nw.b1 - prev.b2;
        if (xn > nw.xinter) {
            int yn = xn + nw.b1;
            conv.emplace_back(lasty, yn, 2, prev.b2);
            int yinter = nw.xinter * 2 + nw.b2;
            conv.emplace_back(yn, yinter, 1, nw.b1);
            lasty = yinter;
            prev = v[i];
        }
    }
    conv.emplace_back(lasty, 0, 2, prev.b2);
    vector<pair<int,int> > p(q);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        p[i] = {k, i};
    }
    sort(p.begin(), p.end(), greater<>());
    int i = 0;
    vector<int> ans(q);
    for (auto it: conv) {
        while (i < q && p[i].first >= it.y2) {
            if (p[i].first <= it.b) {
                ans[p[i].second] = 0;
            } else {
                ans[p[i].second] = (p[i].first - it.b + (it.k - 1)) / it.k;
            }
            ++i;
        }
    }
    for (auto it: ans) {
        cout << it << " ";
    }
    return 0;
}
