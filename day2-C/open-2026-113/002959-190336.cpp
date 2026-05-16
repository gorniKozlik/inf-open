#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast")
using namespace std;
using ll = long long;
ll n, q, l, r, i, k,cnt, f[200002],x;
vector<pair<ll,ll>>a;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (i=0;i<n;i++) {
        cin >> l >> r;
        a.push_back({l,1});
        a.push_back({r,-1});
    }
    sort(a.begin(),a.end());
    for (i=0;i<a.size();i++) {
        cnt+=a[i].second;
        f[min(i+1,2*n-i)]=max(f[min(i+1,2*n-i)], cnt);
    }
    for (i=n;i>=1;i--) {
        f[i]=max(f[i+1],f[i]);
    }
    while (q--) {
        cin >> x;
        cout << (x-f[x]+1)/2 << ' ';
    }
    return 0;
}
