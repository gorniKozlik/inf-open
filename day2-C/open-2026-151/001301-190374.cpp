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
    vector<pair<int, int>> evs;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        seg.push_back({x, y});
        xs.insert(x);
        xs.insert(y);
        evs.push_back({x, 1});
        evs.push_back({y, -1});
    }
    sort(evs.begin(), evs.end());
    deque<pair<int, int>> has;
    int good = 0;
    int full_left = 0, full_right = n;
    for(auto [x, type] : evs){
        if(type == 1){
            good++;
            full_right--;
        }

        if(type == -1){
            good--;
            full_left++;
        }
        int now = good, cost = 0;
        res[now] = min(res[now], cost);
        int fl = full_left, fr = full_right;
        while(fl && fr){
            cost++;
            fl--;
            fr--;
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
    for(int i = n - 2; i >= 0; i--){
        res[i] = min(res[i], res[i + 1]);
    }
    while (q--)
    {
        int k;
        cin >> k;
        cout << res[k] << "\n";
    }
    
}