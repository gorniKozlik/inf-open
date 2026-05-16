#include <bits/stdc++.h>
#define int long long

using namespace std;

int solve(vector <pair <int, int>> &arr, int n) {
    vector <int> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(arr[i].first);
        a.push_back(arr[i].second);
    }
    sort(a.begin(), a.end());
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += (arr[i].first > a[n - 1]);
        cnt += (arr[i].second < a[n]);
    }
    return cnt / 2;
}

bool f(pair <int, int> a, pair <int, int> b) {
    return (a.second < b.second);
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr.begin(), arr.end(), f);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        int ans = 1e9;
        for (int j = k; j <= n; ++j) {
            vector <pair <int, int>> a;
            for (int z = j - k; z < j; ++z) {
                a.push_back(arr[z]);
            }
            ans = min(ans, solve(a, k));
        }
        cout << ans << endl;
    }
    return 0;
}
