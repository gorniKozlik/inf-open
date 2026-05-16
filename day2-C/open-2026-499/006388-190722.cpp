#include<bits/stdc++.h>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    n/=2;
    vector<pair<int, int>> input(n);
    int cnt = 0;
    for (int i = 0; i<n; i++){
        cin >> input[i].first >> input[i].second;
        cnt+=(input[i].first+input[i].second == 2*n+1);
    }
    for (int i = 0; i<q; i++){
        int k;
        cin >> k;
        cout << max(0, n-cnt-1) << endl;
    }
}