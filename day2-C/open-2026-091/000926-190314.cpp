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
    vector<int> pipisa1(cur + 2, -1);
    vector<int> pipisa2(cur + 2, 1e9);
    int cnte = 0;
    int cntb = n;
    int cnt = 0;
    for(int i = 0; i < cur; ++i) {
        cntb -= penis1[i];
        cnt += penis1[i];
        int cost = 0;
        int x = 1;
        pipisa1[cnt] = max(pipisa1[cnt], cnt + min(cntb, cnte) * 2);
        // for(int j = cnt; j <= cnt + min(cntb, cnte) * 2; ++j) {
        //     ans[j] = min(ans[j], cost);
        //     x++;
        //     if(x == 2) {
        //         x = 0;
        //         cost++;
        //     }
        // }
        cost = min(cntb,cnte) + 1;
        pipisa2[cnt + min(cntb,cnte) * 2 + 1] = min(pipisa2[cnt + min(cntb,cnte) * 2 + 1], cost);
        // for(int j = cnt + min(cntb,cnte) * 2 + 1; j <= n; ++j) {
        //     ans[j] = min(ans[j], cost);
        //     cost++;
        // }
        cnte += penis2[i];
        cnt-= penis2[i];
    }
    set<pair<int,int>> st;
    for(int i = 0; i <= n; ++i) {
        if(pipisa1[i] != -1) {
            st.emplace(-i, pipisa1[i]);
        }
        while(st.size() && st.begin()->second < i) {
            st.erase(st.begin());
        }
        if(st.size()) {
            int x = -st.begin()->first;
            int cost = (i - x) / 2 + (i - x) % 2;
            ans[i] = min(ans[i],cost);
        }
    }
    int curp = 1e9;
    for(int i = 0; i <= n; ++i) {
        curp++;
        curp = min(curp, pipisa2[i]);
        ans[i] = min(ans[i],curp);
    }
    for(int j = n-1; j >= 0; --j) {
        ans[j] = min(ans[j], ans[j+1]);
    }
    for(int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}