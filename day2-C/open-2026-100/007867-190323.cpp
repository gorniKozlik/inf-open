#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
struct node {
    int x;
    int type;
};
bool comp(node &n1, node &n2) {
    return n1.x < n2.x;
}
int get_res(vector<pair<int, int>> &a) {
    vector<node> b;
    for (int i = 0; i < a.size(); i++) {
        b.push_back({a[i].first, 1});
        b.push_back({a[i].second, -1});
    }
    sort(b.begin(), b.end(), comp);
    int cur = 0;
    int mxv = 0;
    for (int i = 0; i < b.size(); i++) {
        cur += b[i].type;
        mxv = max(mxv, cur);
    }
    return mxv;
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<int> ans(n + 1);
    int z = get_res(a);
    int add = 0;
    while (z + add != n) {
        int idmnr = 0, idmxl = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i].second < a[idmnr].second) {
                idmnr = i;
            }
            if (a[i].first > a[idmxl].first) {
                idmxl = i;
            }
        }
        pair<int, int> cur1 = {a[idmnr].first, a[idmxl].second};
        pair<int, int> cur2 = {a[idmnr].second, a[idmxl].first};
        ans[z + add + 1]++;
        vector<pair<int, int>> b;
        for (int i = 0; i < a.size(); i++) {
            if (i == idmnr or i == idmxl) continue;
            b.push_back(a[i]);
        }
        a = b;
        z = get_res(a);
        add += 2;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

