#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
vector<int> coords;
int get(int x) {
    return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    int mnr = 1e9, mxl = 0;
    map<int, int> mp;
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
    int mx = 0;
    for (int i = 0; i < s.size(); i++) {
        mx = max(mx, s[i]);
    }
    vector<pair<int, int>> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == mx) {
            st.push_back({i, -1});
            int j = i + 1;
            for (; j < s.size(); j++) {
                if (s[j] != mx) {
                    j--;
                    break;
                }
            }
            st.back().second = j;
            i = j;
        }
    }
    pair<int, int> bst = {0, 1e9};
    for (auto i : st) {
        pair<int, int> tr = {0, 0};
        for (int j = 0; j < n; j++) {
            int x = get(a[j].first);
            int y = get(a[j].second);
            if (x > i.second) {
                tr.first++;
            }
            if (y < i.first) {
                tr.second++;
            }
        }
        if (min(tr.first,  tr.second) > min(bst.first, bst.second)) {
            bst = tr;
        }
    }
    while (q--) {
        int x;
        cin >> x;
        if (x <= mx) {
            cout << 0 << " ";
        }
        else if (x <= mx + 2 * min(bst.first, bst.second)) {
            cout << (x - mx + 1) / 2 << " ";
        }
        else {
            x -= mx;
            cout << min(bst.first, bst.second) + (x - min(bst.first, bst.second) * 2) << " ";
        }
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