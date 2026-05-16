#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<int> l(n),r(n);
    for(int i = 0;i < n;i++){
        cin >> l[i] >> r[i];
    }
    while(q--){
        int k;
        cin >> k;
        cout << k / 2 << "\n";
    }
    return 0;
}
