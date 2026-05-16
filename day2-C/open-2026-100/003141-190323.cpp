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
    vector<int> ans(n + 1);
    int mxv = -inf, left = 0;
    int cur = 0, zakr = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].type == 1) {
            cur++;
        }else {
            cur--;
            zakr++;
        }
        if (cur > mxv) {
            mxv = cur;
            left = zakr;
        }else if (cur == mxv and min(zakr, n - cur - zakr) >= min(left, n - mxv - left)) {
            left = zakr;
        }
    }
    int mnv = min(left, n - mxv - left);
    int j = 0;
    for (int i = 0; i < mnv; i++) {
        ans[mxv + 1 + 2 * i]++;
        j = mxv + 1 + 2 * (i + 1);
    }
    for (int i = j; i <= n; i++) {
        ans[i]++;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    cout << '\n';
}

