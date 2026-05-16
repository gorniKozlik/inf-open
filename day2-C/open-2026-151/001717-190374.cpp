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
        has.push_back({good, min(full_left, full_right)});
    }
    for(int i = 0; i <= n; i++){
        int nw = INF;
        while (!has.empty())
        {
            int want = i - has.back().first;
            if(has.back().second * 2 >= want){
                if(want < 0) want = 0;
                nw = min(nw, (want + 1) / 2);
                break;
            }
            if(has.back().second * 2 + 1 == want){
                nw = min(nw, (want - 1) / 2 + 1);
            }
            has.pop_back();
        }
        res[i] = nw;
    }
    while (q--)
    {
        int k;
        cin >> k;
        cout << res[k] << "\n";
    }
    
}