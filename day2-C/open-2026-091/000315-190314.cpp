#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> a(n);
    map<int,int> x;    
    for(int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;        
        x[a[i].first];
        x[a[i].second];
    }
    vector<int> ans(n + 1,1e9);
    int cur = 0;
    for(auto &u : x) {
        u.second = cur++;
    }
    vector<int> penis1(cur);
    vector<int> penis2(cur);
    for(int i = 0; i < n; ++i) {
        a[i].first = x[a[i].first];
        a[i].second = x[a[i].second];
        penis1[a[i].first]++;
        penis2[a[i].second]++;
    }
    int cnte = 0;
    int cntb = n;
    int cnt = 0;
    for(int i = 0; i < cur; ++i) {
        cntb -= penis1[i];
        cnt += penis1[i];
        int cost = 0;
        int x = 1;
        for(int j = cnt; j <= cnt + min(cntb,cnte)*2; ++j) {
            ans[j] = min(ans[j], cost);
            x++;
            if(x == 2) {
                x = 0;
                cost++;
            }
        }
        for(int j = cnt + min(cntb,cnte)*2 + 1; j <= n; ++j) {
            ans[j] = min(ans[j], cost);
            cost++;
        }
        cnte += penis2[i];
        cnt-= penis2[i];
    }
    for(int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}