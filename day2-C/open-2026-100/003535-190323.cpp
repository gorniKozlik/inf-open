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
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<node> a;
    for (int i = 0; i < n; i++) {
        int l,r;
        cin >> l >> r;
        a.push_back({l, 1});
        a.push_back({r, -1});
    }
    sort(a.begin(), a.end(), comp);
    int mxv = -inf, left = 0;
    int cur = 0, zakr = 0;
    vector<pair<int, int>>ss;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].type == 1) {
            cur++;
        }else {
            cur--;
            zakr++;
        }
        ss.push_back({cur, zakr});
    }
    vector<vector<int>> ans(ss.size(), vector<int>(n + 1));
    for (int k = 0; k < ss.size(); k++) {
        int mnv = min(ss[k].second, n - ss[k].first - ss[k].second);
        int j = 0;
        for (int i = 0; i < mnv; i++) {
            ans[k][ss[k].first + 1 + 2 * i]++;
            j = ss[k].first + 1 + 2 * (i + 1);
        }
        for (int i = j; i <= n; i++) {
            ans[k][i]++;
        }
        for (int i = 1; i <= n; i++) {
            ans[k][i] += ans[k][i - 1];
        }

    }
    while (q--) {
        int k;
        cin >> k;
        int cur = inf;
        for (int i = 0; i < ss.size(); i++) {
            cur = min(cur, ans[i][k]);
        }
        cout << cur << " ";
    }
    cout << '\n';
}

