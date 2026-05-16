#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define int long long
int n;
vector<int> coords;
int get(int x) {
    return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
}

struct str {
    int mx;
    pair<int, int> bst;
};

int gett(str a, int N) {
    if (N <= a.mx) {
        return 0;
    }
    else if (N <= a.mx + 2 * min(a.bst.first, a.bst.second)) {
        return (N - a.mx + 1) / 2;
    }
    else {
        return min(a.bst.first, a.bst.second) + (N - a.mx - min(a.bst.first, a.bst.second) * 2);
    }
}

void solve() {
    int q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        coords.push_back(a[i].first);
        coords.push_back(a[i].second);
        coords.push_back(a[i].second + 1);
        //coords.push_back(a[i].first - 1);
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
    //vector<int> mn(4 * n + 10), mx(4 * n +10);
    //for (int i = 0; i < n; i++) {
      //  int x = get(a[i].first);
      //  int y = get(a[i].second + 1);
      //  mn[y]++;
      //  mn[x - 1]--;
      //  mx[x]++;
      //  mx[y + 1]--;
    //}
    //for (int i = mn.size() - 2; i >= 0; i--) {
      //  mn[i] += mn[i + 1];
    //}
    //for (int i = 1; i < mx.size(); i++) {
      //  mn[i] += mn[i - 1];
    //}
    str bst;// min, mx
    int res = 1e9;
    vector<int> ans(n + 1, 1e9);
    for (int i = 0; i < n; i++) {
        int xx = get(a[i].first);
        pair<int, int> tr = {0, 0};
        for (int j = 0; j < n; j++) {
            int x = a[j].first;
            int y = a[j].second;
            if (x > a[i].first) {
                tr.first++;
            }
            if (y < a[i].first) {
                tr.second++;
            }
        }
        for (int i = 0; i <= n; i++) {
            ans[i] = min(ans[i], gett({s[xx], tr}, i));
        }
        xx = get(a[i].second);
        tr = {0, 0};
        for (int j = 0; j < n; j++) {
            int x = a[j].first;
            int y = a[j].second;
            if (x > a[i].second) {
                tr.first++;
            }
            if (y < a[i].second) {
                tr.second++;
            }
        }
        for (int i = 0; i <= n; i++) {
            ans[i] = min(ans[i], gett({s[xx], tr}, i));
        }
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
