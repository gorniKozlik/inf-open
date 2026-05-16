#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()

const int INF = 1e18;

struct node {
    int pos, type;
};

bool cmp(node a, node b) {
    return a.pos < b.pos;
}

vector<node> a;

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, 1});
        a.push_back({r, -1});
    }
    int sum = 0;
    int mx = 0;
    sort(all(a), cmp);
    int cnt_l = 0;
    int cnt_r = n;
    for (auto [idx, type] : a) {
        sum += type;
        mx = max(mx, sum);
        if (type == -1) {
            cnt_l++;
            cnt_r--;

        }
    }
    //cout << mx << endl;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        int cnt = max(x - mx + 1, 0LL);
        cout << cnt / 2 + cnt % 2 << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}