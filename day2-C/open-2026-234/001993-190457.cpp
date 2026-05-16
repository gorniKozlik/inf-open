#ifndef WILEYNE
#pragma GCC optimize("Ofast")
#endif
#include <bits/extc++.h>

using ll = long long;
const ll LL_INF = 2e18;
using namespace std;
using ordered_set = __gnu_pbds::tree<ll,__gnu_pbds::null_type,less<>,__gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
const int MOD = 998244353;
const int MAX_N = (int)2e5+10;
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();

int ans[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef WILEYNE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int n,q;
    cin>>n>>q;
    vector<pair<int,int>>v(n);
    for (auto &c:v) cin>>c.first>>c.second;
    vector<pair<int,int>>events;
    for (auto [l,r]:v) {
        events.emplace_back(l,1);
        events.emplace_back(r,-1);
    }
    sort(events.begin(), events.end());
    set<pair<int,int>>st;
    int bal = 0;
    for (int i = 0;i<events.size()-1;++i) {
        bal+=events[i].second;
        st.insert({bal,min(i+1,2*n-i-1)});
    }
    for (int i = 1;i<=n;++i) {
        auto it = st.end();
        --it;
        while (it->second<i) {
            st.erase(it);
            it = st.end();
            --it;
        }
        if (it->first >= i) {
            ans[i] = 0;
        }
        else {
            ans[i] = (i-it->first+1)/2;
        }
    }
    while (q--) {
        int k;
        cin>>k;
        cout<<ans[k]<<" ";
    }
    return 0;
}