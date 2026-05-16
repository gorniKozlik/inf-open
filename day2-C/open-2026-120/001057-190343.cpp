#include <bits/stdc++.h>

using namespace std;

#ifndef lisie_bimbi
#define endl '\n'
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,bmi2,fma")
#endif

using ll = long long;

const int N = 500'010;
const int inf = 1'000'000'000;

struct node{
    int mx;
    int mod;
};

struct segtree{
    node d[4 * N];
    vector<int> a;
    int n;
    void build(int u, int l, int r){
        n = a.size();
        d[u].mod = 0;
        if(l + 1 == r){
            d[u].mx = a[l];
        }else{
            int m = (l + r) / 2;
            build(u * 2 + 1, l, m);
            build(u * 2 + 2, m, r);
            d[u].mx = max(d[u * 2 + 1].mx, d[u * 2 + 2].mx);
        }
    }
    void push(int u, int l, int r){
        if(d[u].mod != 0){
            if(l + 1 != r){
                d[u * 2 + 1].mod += d[u].mod;
                d[u * 2 + 2].mod += d[u].mod;
            }
            d[u].mx += d[u].mod;
            d[u].mod = 0;
        }
    }
    int get(int u, int l, int r, int ql, int qr){
        if((ql >= r) || (qr <= l)){
            return -inf;
        }
        push(u, l, r);
        if((ql <= l) && (r <= qr)){
            return d[u].mx;
        }
        int m = (l + r) / 2;
        return max(get(u * 2 + 1, l, m, ql, qr), get(u * 2 + 2, m, r, ql, qr));
    }
    void update(int u, int l, int r, int ql, int qr, int dd){
        if((ql >= r) || (qr <= l)){
            return;
        }
        if((ql <= l) && (r <= qr)){
            d[u].mod += dd;
            return;
        }
        push(u, l, r);
        int m = (l + r) / 2;
        update(u * 2 + 1, l, m, ql, qr, dd);
        update(u * 2 + 2, m, r, ql, qr, dd);
        push(u * 2 + 1, l, m);
        push(u * 2 + 2, m, r);
        d[u].mx = max(d[u * 2 + 1].mx, d[u * 2 + 2].mx);
    }
    int gg(){
        push(0, 0, n);
        return d[0].mx;
    }
};

segtree st;

void solve(){
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> z;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        z.emplace_back(l, 1);
        z.emplace_back(r, -1);
    }
    sort(z.begin(), z.end());
    vector<int> b = {0};
    for(auto [j, i] : z){
        b.push_back(b.back() + i);
    }
    vector<int> plus, minus;
    for(int i = 0; i < z.size(); i++){
        if(z[i].second == 1){
            plus.push_back(i);
        }else{
            minus.push_back(i);
        }
    }
    reverse(plus.begin(), plus.end());
    st.a = b;
    int N = b.size();
    st.build(0, 0, N);
    vector<int> ans(n + 1, inf);
    ans[st.gg()] = 0;
    for(int i = 0; i < minus.size(); i++){
        int left = minus[i], right = plus[i];
        if(right < left){
            break;
        }
        st.update(0, 0, N, left + 1, right + 1, 2);
        ans[st.gg()] = min(ans[st.gg()], i + 1);
    }
    for(int i = n - 1; i >= 0; i--){
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for(int i = 0; i < q; i++){
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
    cout << endl;
}

signed main(){
#ifdef lisie_bimbi
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);   
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif         
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}