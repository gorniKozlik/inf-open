#include<bits/stdc++.h>
using namespace std;

#define int long

const int MOD = 998244353, MAXN = 3031, INF = 1e18;

int res[MAXN];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 1; i < MAXN; i++) res[i] = INF;
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> seg;
    set<int> xs;
    vector<int> has;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        seg.push_back({x, y});
        xs.insert(x);
        xs.insert(y);
        has.push_back(x);
        has.push_back(y);
    }
    sort(has.begin(), has.end());
    for(auto x : xs){
        int full_left = 0, full_right = 0;
        int good = 0;
        int free_left = 0, free_right = 0;
        for(auto y : has){
            if(y < x) free_left++;
            if(y > x) free_right++;
        }
        for(auto [l, r] : seg){
            if(r < x) full_left++;
            if(x < l) full_right++;
            if(l <= x && x <= r){
                good++;
            }
        }
        int now = good, cost = 0;
        res[now] = min(res[now], cost);
        while(full_left && full_right){
            cost++;
            full_left--;
            full_right--;
            now += 2;
            res[now - 1] = min(res[now - 1], cost);
            res[now] = min(res[now], cost);
        }
        if(now < n){
            cost++;
            now+=1;
            res[now] = min(res[now], cost);
        }
    }
    while (q--)
    {
        int k;
        cin >> k;
        cout << res[k] << "\n";
    }
    
}