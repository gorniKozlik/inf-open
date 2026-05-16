#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
#include <random>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define int long long

using namespace std;

mt19937 rnd(52);

typedef long long ll;
typedef long double ld;

const ll MAXN = 1e5 + 1;
const ll MOD = 998244353;
const ll INF = 1e18;

struct Node{
    int pos, type, ind;

    Node(): pos(0), type(0), ind(0) {}

    Node(int pos, int type, int ind): pos(pos), type(type), ind(ind) {}
};

bool comp(Node a, Node b){
    return a.pos < b.pos;
}


void solve(){
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> arr(n);
    vector<int> soot;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        arr[i] = {l, r};
        soot.push_back(l);
        soot.push_back(r);
    }
    sort(all(soot));
    for(int i = 0; i < n; i++){
        arr[i].first = lower_bound(all(soot), arr[i].first) - soot.begin();
        arr[i].second = lower_bound(all(soot), arr[i].second) - soot.begin();
    }
    vector<Node> sob;
    for(int i = 0; i < n; i++){
        sob.emplace_back(arr[i].first, 1, i);
        sob.emplace_back(arr[i].second, -1, i);
    }
    sort(all(sob), comp);
    vector<pair<int,int>> scanline(2 * n);
    int cnt = 0;
    int left = 0;
    for(auto x: sob){
        left++;
        if(x.type == 1){
            cnt++;
        }
        if(x.type == -1){
            cnt--;
        }
        scanline[x.pos] = {cnt, left};
    }
    sort(rall(scanline));
    vector<pair<int, int>> reqs(q);
    for(int i = 0; i < q; i++){
        int k;
        cin >> k;
        reqs[i] = {k , i};
    }
    sort(all(reqs));
    int st = 0;
    vector<int> ans(q);
    for(int i = 0; i < 2 * n && st < q; i++){
        while(st < q && reqs[st].first <= scanline[i].first + min(scanline[i].second - scanline[i].first, 2 * n - scanline[i].second - scanline[i].first)){
            if(reqs[st].first <= scanline[i].first){
                ans[reqs[st].second] = 0;
                st++;
                continue;
            }
            else{
                ans[reqs[st].second] = ((reqs[st].first - scanline[i].first) - 1) / 2 + 1;
                st++;
                continue;
            }
        }
    }
    for(auto x: ans){
        cout << x << " ";
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}