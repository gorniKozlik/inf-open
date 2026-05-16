#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pii pair<int, int>
#define ff first
#define ss second
#define ld long double
#define pb push_back
#define ins insert
#define int ll

mt19937 rnd(1488);

void solve(){
    int n, q;
    cin >> n >> q;
    vector<pii> sc;
    vector<int> c2;
    vector<pii> c(n);
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        c[i] = {l, r};
        c2.pb(l);
        c2.pb(r);
        sc.pb({l, -1});
        sc.pb({r, 1});
    }
    sort(all(c2));
    sort(all(sc));
    int mx = 0, bal = 0;
    for (auto [x, y]:sc){
        bal -= y;
        mx = max(mx, bal);
    }
    vector<int> ans(n + 1, n);
    for (int i = 1; i <= mx; i++){
        ans[i] = 0;
    }
    int cntr = 0;
    int cntl = n;
    bal = 0;
    int j = 0;
    vector<array<int, 3>> sc1;
    vector<array<int, 3>> sc2;
    for (int i = 0; i + 1 < 2 * n; i++){
        int l = c2[i];
        int r = c2[i + 1];
        while (j < sc.size() && sc[j].ff <= l){
            if (sc[j].ss == 1){
                cntr++;
            }
            else{
                cntl--;
            }
            j++;
        }
        bal = n - cntl - cntr;
        if (bal % 2 == 0){
            sc1.pb({bal, bal, 1});
            sc1.pb({bal + min(cntl, cntr) * 2 + 1, bal, -1});
        }
        else{
            sc2.pb({bal, bal, 1});
            sc2.pb({bal + min(cntl, cntr) * 2 + 1, bal, -1});
        }
    }
    sort(all(sc1));
    sort(all(sc2));
    multiset<int> st1;
    multiset<int> st2;
    int j1 = 0;
    int j2 = 0;
    for (int i = 0; i <= n; i++){
        while (j1 < sc1.size() && sc1[j1][0] == i){
            if (sc1[j1][2] == 1){
                st1.ins(sc1[j1][1]);
            }
            else{
                st1.erase(st1.find(sc1[j1][1]));
            }
            j1++;
        }
        while (j2 < sc2.size() && sc2[j2][0] == i){
            if (sc2[j2][2] == 1){
                st2.ins(sc2[j2][1]);
            }
            else{
                st2.erase(st2.find(sc2[j2][1]));
            }
            j2++;
        }
        if (st1.size()){
            ans[i] = min(ans[i], (i - *st1.rbegin() + 1) / 2);
        }
        if (st2.size()){
            ans[i] = min(ans[i], (i - *st2.rbegin() + 1) / 2);
        }
    }
    while (q--){
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}

int32_t main(){
    cin.tie(0)->ios_base::sync_with_stdio(0);
    #ifdef podureman
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // podureman
    int _ = 1;
    //cin >> _;
    while (_--){
        solve();
    }
}
