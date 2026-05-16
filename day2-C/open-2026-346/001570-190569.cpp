#include <bits/stdc++.h>

using namespace std;

struct El {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(2 * n);
    vector<El> b;
    for (int i = 0; i < 2 * n; i += 2) {
        cin >> a[i] >> a[i + 1];
        b.push_back({a[i], a[i + 1]});
    }
    sort(a.begin(), a.end());
    int mx = a[n - 1];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (b[i].r <= mx || mx <= b[i].l) {
            cnt++;
        }
    }
    cout << cnt / 2;
}
