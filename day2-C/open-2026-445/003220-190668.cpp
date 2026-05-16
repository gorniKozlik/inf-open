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
    vector<str> us;
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
        us.push_back({s[xx], tr});
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
        us.push_back({s[xx], tr});
    }
    while (q--) {
        int x;
        cin >> x;
        int ans = 1e9;
        for (int i = 0; i < us.size(); i++) {
            if (x <= us[i].mx) {
                ans = min(ans, 0);
            }
            else if (x <= us[i].mx + 2 * min(us[i].bst.first, us[i].bst.second)) {
                ans = min(ans, (x - us[i].mx + 1) / 2);
            }
            else {
                ans = min(ans, min(us[i].bst.first, us[i].bst.second) + (x - us[i].mx - min(us[i].bst.first, us[i].bst.second) * 2));
            }
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