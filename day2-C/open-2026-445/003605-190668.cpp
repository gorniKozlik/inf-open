#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
vector<int> coords;
int get(int x) {
    return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
}

struct str {
    int mx;
    pair<int, int> bst;
};

pair<int, int> getm(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        if (a.second > b.second) {
            return a;
        }
        return b;
    }
    if (a.first > b.first) {
        return a;
    }
    return b;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        coords.push_back(a[i].first);
        coords.push_back(a[i].second);
        coords.push_back(a[i].second + 1);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    vector<int> s(3 * n + 10);
    for (int i = 0; i < n; i++) {
        s[get(a[i].first)]++;
        s[get(a[i].second + 1)]--;
    }
    for (int i = 1; i < s.size(); i++) {
        s[i] += s[i - 1];
    }
    pair<int, int> us = {0, 0};//min and mx
    for (int i = 0; i < n; i++) {
        int xx = get(a[i].first);
        pair<int, int> tr = {0, 0};
        for (int j = 0; j < n; j++) {
            int x = get(a[j].first);
            int y = get(a[j].second);
            if (x > xx) {
                tr.first++;
            }
            if (y < xx) {
                tr.second++;
            }
        }
        us = getm(us, {abs(tr.first - tr.second), s[xx]});
        xx = get(a[i].second);
        tr = {0, 0};
        for (int j = 0; j < n; j++) {
            int x = get(a[j].first);
            int y = get(a[j].second);
            if (x > xx) {
                tr.first++;
            }
            if (y < xx) {
                tr.second++;
            }
        }
        us = getm(us, {abs(tr.first - tr.second), s[xx]});
    }
    while (q--) {
        int x;
        cin >> x;
        int ans = 1e9;
        if (x <= us.second) {
            ans = min(ans, 0);
        }
        else if (x <= us.second + 2 * us.first) {
            ans = min(ans, (x - us.second + 1) / 2);
        }
        else {
            ans = min(ans, us.first + (x - us.second - us.first * 2));
        }
        cout << ans << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}