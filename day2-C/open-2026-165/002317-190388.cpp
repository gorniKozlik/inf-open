#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << k / 2 << endl;
    }
    return 0;
}
