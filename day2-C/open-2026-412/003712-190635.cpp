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
    int cnt2 = 0;
    vector<pair<int, int>> cur;
    for (auto [idx, type] : a) {
        sum += type;
        mx = max(mx, sum);
        if (type == -1) {
            cnt_l++;
        }
        if (type == 1) {
            cnt_r--;
        }

        cnt2 = min(cnt_l, cnt_r);

        cur.push_back({sum, cnt2});

    }
    //cout << mx << ' ' << cnt2 << endl;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        int tmp = x;
        int ans = INF;
        int cnt = 0;
        for (auto [mx, cnt2] : cur) {
            cnt++;
            if (cnt > 1000) {
                break;
            }
            x = tmp;
            x -= mx;
            x = max(0LL, x);
            if (x == 0) {
                ans = min(0LL, ans);
            } else if (x / 2 + x % 2 <= cnt2) {
                ans = min(x / 2 + x % 2, ans);
            } else {
                ans = min(x - cnt2 * 2 + cnt2, ans);
            }
         //   cout << "ans = " << ans << endl;
        }
        cout << ans << ' ';
     //   cout << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}