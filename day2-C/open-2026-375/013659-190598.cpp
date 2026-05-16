#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll

#pragma gcc optimize("O3")
#pragma gcc target("avx3,avx2")

using pii = pair<int, int>;

struct SegTree{

    vector<int> t;
    vector<int> psh;

    SegTree(int n): t(4 * n), psh(4 * n){}

    void push(int v, int l, int r){
        t[v] += psh[v];
        if(r - l > 1){
            psh[v * 2 + 1] += psh[v];
            psh[v * 2 + 2] += psh[v];
        }
        psh[v] = 0;
    }

    void update(int v, int l, int r, int ql, int qr, int x){
        push(v, l, r);
        if(qr <= l || r <= ql){
            return;
        }
        if(ql <= l && r <= qr){
            psh[v] += x;
            push(v, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(v * 2 + 1, l, mid, ql, qr, x);
        update(v * 2 + 2, mid, r, ql, qr, x);
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
    }

    int get(int v, int l, int r, int ql, int qr){
        if(v == -1 || qr <= l || r <= ql){
            return 0;
        }
        push(v, l, r);
        if(ql <= l && r <= qr){
            return t[v];
        }
        int mid = (l + r) / 2;
        return max(get(v * 2 + 1, l, mid, ql, qr), get(v * 2 + 2, mid, r, ql, qr));
    }
};

unordered_map<int, int> comp, decomp;
void build_compress(const vector<int> &a){
    auto b = a;
    sort(b.begin(), b.end());
    int cnt = 0;
    comp[b[0]] = 0;
    for(int i = 1; i < a.size(); i++){
        if(b[i] != b[i - 1]){
            cnt ++;
            comp[b[i]] = cnt;
            decomp[cnt] = b[i];
        }
    }
}

void solve(){
    int n,  q;
    cin >> n >> q;
    set<pii> minr;
    set<pii> maxl;
    SegTree st(2 * n);
    vector<int> vals;
    for(int i = 0; i < 2 * n; i++){
        int x;
        cin >> x;
        vals.push_back(x);
    }
    build_compress(vals);
    int j = 0;
    for(int i = 0; i < n; i++){
        int l = comp[vals[j++]];
        int r = comp[vals[j++]];
        minr.insert({r, l});
        maxl.insert({-l, r});
        st.update(0, 0, 2 * n, l, r + 1, 1);
    }
    vector<int> ans(n + 1);
    int mx = st.t[0] + 1;
    int i = 1;
    while(minr.size() && mx <= n){
        auto [r1, l1] = *minr.begin();
        auto [l2, r2] = *maxl.begin();
        l2 = -l2;
        if(l1 == l2 && r1 == r2 && r1 >= l2){
            break;
        }
        st.update(0, 0, 2 * n, r1, l2 + 1, 1);
        st.update(0, 0, 2 * n, r1 + 1, l2, 1);
        for(; mx <= st.t[0]; mx++){
            ans[mx] = i;
        }
        i++;
        minr.erase({r1, l1});
        minr.erase({r2, l2});
        maxl.erase({-l1, r1});
        maxl.erase({-l2, r2});
        // minr.insert({l2, l1});
        // maxl.insert({-l1, l2});
        // minr.insert({r2, r1});
        // maxl.insert({-r1, r2});
        minr.insert({l2, r1});
        maxl.insert({-r1, l2});
    }
    while(q--){
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << '\n';
}

signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}