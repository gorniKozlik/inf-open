#include <iostream>
#include <vector>
#include <algorithm>
#include<set>
#include <cinttypes>
#include <string>
#include <map>

using namespace std;

int main() {
    int64_t n, k;
    cin >> n >> k;
    vector<pair<int64_t, int64_t> > a(n);
    vector<int64_t> now(2 * n);
    map<int64_t, int64_t> ma;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        now[2 * i] = a[i].first;
        now[2 * i + 1] = a[i].second;
    }
    sort(now.begin(), now.end());
    for (int i = 0; i < 2 * n; i++) {
        ma[now[i]] = i;
    }
    vector<int64_t> nowi(2*n);
    for (auto [i, j] : a) {
//        cout << i << ' ' << ma[i] << ' ' << j << ' ' << ma[j] << '\n';
        nowi[ma[i]] = 1;
        nowi[ma[j]] = -1;
    }
    for (int i = 1; i < 2*n; i++) {
        nowi[i] += nowi[i - 1];
//        cout << i << ' ' << nowi[i] << '\n';
    }
    nowi.pop_back();
    vector<int64_t> nowe(n);
    nowe[0] = (n - nowi[n-1]) / 2;
    for (int i = 1; i < n; i++) {
        nowe[i] = nowe[i - 1];
        if (i > 1) {
            nowe[i] = max(int64_t(0), nowe[i - 2] - 1);
        }
        nowe[i] = min(nowe[i], max(int64_t(0), n - max(nowi[n - 1 + i], nowi[n - 1 - i]) - i) / 2);
    }
    while (k--) {
        int64_t x;
        cin >> x;
        cout << nowe[n - x] << ' ';
    }
    cout << '\n';
    return 0;
}
