#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double


int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<array<int,2>> a(n),t;
    for (int i= 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        t.push_back({a[i][0],-1});
        t.push_back({a[i][1],1});
    }
    sort(t.begin(),t.end());
    vector<int> h,g(q,1e18);
    for (int i = 0; i < q; ++i){
        int k;
        cin >> k;
        h.push_back(k);
    }
    vector<int> ans(n + 1,1e18);
    int b = 0;
    int x = 0;
    for (auto v : t) {
        b-=v[1];
        if (v[1] == -1) {
            int k = b;
            int y = n - k - x;
            for (int w = 0; w < q; ++w) {
                if (h[w] <= k) g[w] = 0;
                else if (h[w]<=k + 2 * min(x,y)) {
                    g[w] = min(g[w],1 + (h[w] - k) / 2);
                }else {
                    g[w] = min(g[w],h[w] - (k + 2 * min(x,y)) + min(x,y));
                }
            }
        }else {
            x++;
        }
    }
    for (int i : g) cout << i << ' ';
}