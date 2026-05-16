#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> arr(n);
    vector <int> a;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        a.push_back(arr[i].first);
        a.push_back(arr[i].second);
    }
    sort(arr.begin(), arr.end());
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += (arr[i].first > a[n - 1]);
        cnt += (arr[i].second < a[n]);
    }
    cout << cnt / 2 << endl;
    return 0;
}
