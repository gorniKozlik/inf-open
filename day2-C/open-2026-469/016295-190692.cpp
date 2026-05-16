#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
using pii = pair<int,int>;
const int inf = 2e9;
const int M = 998244353;
const ld eps = 1e-9;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    int n,m;
    cin >> n>> m;
    vector<int> a(n);
    for (int i = 0; i < n;i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    int last = a[0];
    for (int i = 1; i <n;i++) {
        if (a[i]-a[0] == 1) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}