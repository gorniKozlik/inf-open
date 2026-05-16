#include <bits/stdc++.h>

using namespace std;

long long inf =  1e18;

int main() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    long long n, q;
    cin >> n >> q;
    vector<pair<long long, long long>> evs;
    vector<long long> maxv(n);
    set<pair<long long, long long>> cans;
    set<long long> ss;
    for(long long i = 0; i < n; i++){
        long long l, r;
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
    long long opens = 0;
    long long closed = 0;
    for(auto [x, tip] : evs){
        if(tip == -1){
            opens++;
        } else if(tip == 1){
            closed++;
            opens--;
        } else{
            long long maxi = min(closed, n - opens - closed) * 2 + opens;
            cans.insert({-maxi, opens});
        }
    }
    // for(auto [a, b] : cans){
    //     cout << a << " " << b << '\n';
    // }
    set<pair<long long, long long>> maxx;
    long long maxnow = 0;
    for(auto [mx, op] : cans){
        maxnow = op;
        maxx.insert({-mx, maxnow});
    }
    // for(auto [a, b] : maxx){
    //     cout << a << " " << b << '\n';
    // }
    vector<pair<long long, long long>> vc;
    for(auto [a, b] : maxx){
        vc.push_back({a, b});
    }
    maxx = {};
    long long maxb = 0;
    for(long long i = vc.size() - 1; i >= 0; i--){
        maxb = max(maxb, vc[i].second);
        maxx.insert({vc[i].first, maxb});
    }
    while(q--){
        long long k;
        cin >> k;
        long long ans = 1e18;
        auto i = maxx.lower_bound({k, -inf});
        long long b = (*i).second;
        long long dos = max((long long)0, (k - b));
        dos = (dos + 1) / 2;
        ans = min(ans, dos);
        cout << ans << '\n';
    }
}
