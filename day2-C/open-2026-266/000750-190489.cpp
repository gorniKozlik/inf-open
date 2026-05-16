#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;

    cin >> n >> q;

    vector<pair<int, int>> segments;

    for (int i = 0; i < n; ++i){
        int l, r;
        cin >> l >> r;
        segments.emplace_back(l, r);
    }

    vector<int> ans(n, 0);

    for (int i = 2; i <= n; ++i){
        ans[i-1] = i/2;
    }

    for (int i = 0; i < q; ++i){
        int k;
        cin >> k;
        cout << ans[k-1] << " ";
    }

    return 0;
}