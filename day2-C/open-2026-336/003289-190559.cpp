#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#define int long long
#define ss second
#define ff first
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define ll long long
using namespace std;
//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag,
//tree_order_statistics_node_update> ordered_set;
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll_loops")
const ll inf = 1e9 + 10;
const ll mod = 1e9 + 7;
const ll maxn = 4e5 + 10;


int tree[maxn * 4];
int add[maxn * 4];


void push(int ind, int l, int r) {
    tree[ind] += add[ind];
    if (l != r) {
        add[ind * 2] += add[ind];
        add[ind * 2 + 1] += add[ind];
    }
    add[ind] = 0;
}


void upd(int ind, int l, int r, int ql, int qr, int v) {
    push(ind, l, r);
    if (ql <= l && r <= qr) {
        add[ind] += v;
        push(ind, l, r);
        return;
    }
    if (l > qr || r < ql)
        return;
    int m = (r + l) / 2, ls = ind * 2, rs = ind * 2 + 1;
    upd(ls, l, m, ql, qr, v);
    upd(rs, m + 1, r, ql, qr, v);
    tree[ind] = max(tree[ls], tree[rs]);
}


// int get(int ind, int l, int r, int ql, int qr) {
//     push(ind, l, r);
//     if (ql <= l && r <= qr)
//         return tree[ind];
//     if (l > qr || r < ql)
//         return 0;
//     int m = (r + l) / 2, ls = ind * 2, rs = ind * 2 + 1;
//     int ansl = get(ls, l, m, ql, qr);
//     int ansr = get(rs, m + 1, r, ql, qr);
//     return min(ansl, ansr);
// }


void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> segs(n);
    vector<int> a;
    for (int i = 0; i < n; i++) {
        cin >> segs[i].ff >> segs[i].ss;
        a.push_back(segs[i].ff);
        a.push_back(segs[i].ss);
    }
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    set<pair<int, int>> begins;
    set<pair<int, int>> ends;
    for (int i = 0; i < n; i++) {
        segs[i].ff = lower_bound(all(a), segs[i].ff) - a.begin();
        segs[i].ss = lower_bound(all(a), segs[i].ss) - a.begin();
        upd(1, 0, maxn - 1, segs[i].ff, segs[i].ss, 1);
        //cout << segs[i].ff << " " << segs[i].ss << endl;
        begins.insert({-segs[i].ff, segs[i].ss});
        ends.insert({segs[i].ss, segs[i].ff});
    }
    //cout << endl;
    //
    vector<pair<int, int>> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i].ff;
        b[i].ss = i;
    }
    //
    vector<int> ans(n + 10);
    int last = 0;
    int plus = 0;
    while (true) {
        push(1, 0, maxn - 1);
        int cur = tree[1];
        for (int j = last; j <= cur; j++)
            ans[j] = plus;
        if (cur >= n)
            break;
        last = cur + 1;
        plus++;
        //cout << cur << endl;

        auto [rt, rts] = *begins.begin();
        begins.erase(begins.begin());
        auto [lt, lts] = *ends.begin();
        ends.erase(ends.begin());
        rt = -rt;
        //cout << lt << " " << rt << endl;
        upd(1, 0, maxn - 1, lt + 1, rt - 1, 2);
        upd(1, 0, maxn - 1, lt, lt, 1);
        upd(1, 0, maxn - 1, rt, rt, 1);
    }

    for (auto el : b) {
        cout << ans[el.ff] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ::freopen("input.txt", "r", stdin);
    ::freopen("output.txt", "w", stdout);

    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}
