#include <bits/stdc++.h>

using namespace std;

int inf =  1e9;

int main() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> evs;
    vector<int> maxv(n);
    set<pair<int, int>> maxx;
    set<int> ss;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        evs.push_back({l, -1});
        evs.push_back({r, 1});
        ss.insert(l);
        ss.insert(r);
    }
    for(auto ch : ss){
        evs.push_back({ch, -2});
    }
    sort(evs.begin(), evs.end());
    int opens = 0;
    int closed = 0;
    for(auto [x, tip] : evs){
        if(tip == -1){
            opens++;
        } else if(tip == 1){
            closed++;
            opens--;
        } else{
            int maxi = min(closed, n - opens - closed) * 2 + opens;
            maxx.insert({maxi, opens});
        }
    }
    vector<pair<int, int>> vc;
    vc.reserve(maxx.size());
    for(auto [a, b] : maxx){
        vc.push_back({a, b});
    }
    maxx = {};
    int maxb = 0;
    for(int i = vc.size() - 1; i >= 0; i--){
        maxb = max(maxb, vc[i].second);
        maxx.insert({vc[i].first, maxb});
    }
    while(q--){
        int k;
        cin >> k;
        int ans = 1e18;
        auto i = maxx.lower_bound({k, -inf});
        int b = (*i).second;
        int dos = max((int)0, (k - b));
        dos = (dos + 1) / 2;
        ans = min(ans, dos);
        cout << ans << '\n';
    }
}
