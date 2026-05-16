#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
#include <stack>
#include <deque>
#include <queue>
#include <climits>
#include <cmath>
#include <bitset>
#include <string>
#include <utility>
#include <cstring>
#include <iomanip>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define mid (l + r) / 2
//#define int long long

constexpr int maxn = 200'002;
int l[maxn];
int r[maxn];
int k[maxn];
struct Event {
    int pos;
    int type;
};
bool operator<(Event a, Event b) {
    if (a.pos == b.pos) return a.type > b.type;
    return a.pos < b.pos;
}
vector<Event> e;
int a[maxn];
struct Node {
    int mxpref;
    int sum;
};
Node tree[8 * maxn];
void build(int x, int l, int r) {
    if (r - l == 1) {
        tree[x] = {max(e[l].type, 0), e[l].type};
        return;
    }
    build(2 * x + 1, l, mid);
    build(2 * x + 2, mid, r);
    tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
    tree[x].mxpref = max(tree[2 * x + 1].mxpref, tree[2 * x + 1].sum + tree[2 * x + 2].mxpref);
}
Node getseg(int x, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) {
        return tree[x];
    }
    if (l >= qr || r <= ql) {
        return {INT_MIN, 0};
    }
    Node ans;
    Node ans1 = getseg(2 * x + 1, l, mid, ql, qr);
    Node ans2 = getseg(2 * x + 2, mid, r, ql, qr);
    ans.sum = ans1.sum + ans2.sum;
    ans.mxpref = max(ans1.mxpref, ans1.sum + ans2.mxpref);
    return ans;
}
void setree(int x, int l, int r, int q, int to) {
    if (r - l == 1) {
        if (to == 1) {
            e[l].type = to;
            tree[x] = {1, 1};
        } else {
            e[l].type = to;
            tree[x] = {0, -1};
        }
        return;
    }
    if (q < mid) {
        setree(2 * x + 1, l, mid, q, to);
    } else {
        setree(2 * x + 2, mid, r, q, to);
    }
    tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
    tree[x].mxpref = max(tree[2 * x + 1].mxpref, tree[2 * x + 1].sum + tree[2 * x + 2].mxpref);
}
int pers() {
    int cnt = 0;
    int mx = 0;
    for (Event i : e) {
        if (i.type == true) {
            cnt++;
        } else {
            cnt--;
        }
        mx = max(mx, cnt);
    }
    return mx;
}
int ans[maxn];
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int li, ri; cin >> li >> ri;
        l[i] = li;
        r[i] = ri;
        e.push_back({li, 1});
        e.push_back({ri, -1});
    }
    sort(all(e));
    build(0, 0, e.size());
    int nw = pers();
    for (int i = 0; i <= nw; i++) {
        ans[i] = 0;
    }
    int opers = 0;
    int lind = e.size() - 1;
    int rind = 0;
    for (int i = nw + 1; i <= n; i++) {
        if (nw >= i) {
            ans[i] = opers;
            continue;
        }
        while (e[rind].type == 1) {
            rind++;
        }
        while (e[lind].type == -1) {
            lind--;
        }
        setree(0, 0, e.size(), lind, -1);
        setree(0, 0, e.size(), rind, 1);
        nw = getseg(0, 0, e.size(), 0, e.size()).mxpref;
        opers++;
        ans[i] = opers;
    }
    for (int iq = 0; iq < q; iq++) {
        int ki; cin >> ki;
        cout << ans[ki] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
