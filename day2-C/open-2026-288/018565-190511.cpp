#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define pb push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const int INF = 1e18, MOD = 998244353;

struct Node{
    int val = 0, add = 0;
};

vector<Node> tree;

void push(int i, int l, int r){
    tree[i].val += tree[i].add;
    if (l + 1 == r){
        tree[i].add = 0;
        return;
    }
    tree[i * 2 + 1].add += tree[i].add;
    tree[i * 2 + 2].add += tree[i].add;
    tree[i].add = 0;
}

void upd(int i, int l, int r, int q_l, int q_r, int x){
    push(i, l, r);
    if (r <= q_l or q_r <= l) return;
    if (q_l <= l and r <= q_r){
        tree[i].add += x;
        push(i, l, r);
        return;
    }
    int m = (l + r) / 2;
    upd(i * 2 + 1, l, m, q_l, q_r, x);
    upd(i * 2 + 2, m, r, q_l, q_r, x);
    tree[i].val = max(tree[i * 2 + 1].val, tree[i * 2 + 2].val);
}

int get_m(int i, int l, int r, int q_l, int q_r){
    push(i, l, r);
    if (r <= q_l or q_r <= l) return -INF;
    if (q_l <= l and r <= q_r) return tree[i].val;
    int m = (l + r) / 2;
    return max(get_m(i * 2 + 1, l, m, q_l, q_r), get_m(i * 2 + 2, m, r, q_l, q_r));
}

void solve(){
    int q, n; cin >> n >> q;
    tree.resize(8 * n + 10);
    vector<pair<int, int>> event(n);
    for (auto &ell: event) cin >> ell.ff >> ell.ss;
    vector<int> koo;
    for (auto ell: event){
        koo.pb(ell.ff); koo.pb(ell.ss); koo.pb(ell.ss+1);
    }
    sort(all(koo));
    koo.erase(unique(all(koo)), koo.end());
    for (auto &ell: event){
        ell.ff = (koo.lower_bound(ell.ff) - koo.begin());
        ell.ss = (koo.lower_bound(ell.ss) - koo.begin());
    }
    multiset<pair<int, int>> lg, rg;
    for (int i = 0; i < n; i++){
        lg.insert(event[i]);
        rg.insert({event[i].ss, event[i].ff});
    }
    vector<int> ans(n+1, INF);
    int cnt = 0, l = 0;
    n = koo.size();
    tree.resize(4 * n);
    for (auto &ell: event){
        upd(0, 0, n, ell.ff, ell.ss+1, 1);
    }
    for (int i = 0; i < n+1; i++){
        int mx = get_m(0, 0, n, 0, n);
        while (l <= mx){
            ans[l] = min(ans[l], cnt);
            l++;
        }
        pair<int, int> t2 = *lg.rbegin(), t1 = *rg.begin();

        t1 = {t1.ss, t1.ff};
        upd(0, 0, n, t1.ff, t1.ss+1, -1);
        upd(0, 0, n, t2.ff, t2.ss+1, -1);
        lg.erase(lg.find(t1));
        lg.erase(lg.find(t2));
        upd(0, 0, n, t1.ff, t2.ff+1, 1);
        upd(0, 0, n, t1.ss, t2.ss+1, 1);
        lg.insert({t1.ff, t2.ff});
        lg.insert({t1.ss, t2.ss});
        rg.erase(rg.find({t1.ss, t1.ff}));
        rg.erase(rg.find({t2.ss, t2.ff}));
        rg.insert({t2.ff, t1.ff});
        rg.insert({t2.ss, t1.ss});
        cnt++;
    }
    for (int i = 0; i < q; i++){
        int k; cin >> k;
        cout << ans[k] << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int t = 1; //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
