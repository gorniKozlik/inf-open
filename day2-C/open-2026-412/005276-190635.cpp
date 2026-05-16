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

vector<pair<int, int>> b;


int f(int idx, int x) {
    int mx = b[idx].first;
    int cnt2 = b[idx].second;
    int ans = INF;
    x -= mx;
    x = max(0LL, x);
    if (x == 0) {
        ans = min(0LL, ans);
    } else if (x / 2 + x % 2 <= cnt2) {
        ans = min(x / 2 + x % 2, ans);
    } else {
        ans = min(x - cnt2 * 2 + cnt2, ans);
    }
    return ans;
}

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
    unordered_map<int, int> cur;
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
        //if (cnt2 > cur.back().second)
        cur[sum] = max(cur[sum], cnt2);


    }


    for (auto to : cur) {
        b.push_back(to);
    }
    //sort(all(cur));
    //cout << mx << ' ' << cnt2 << endl;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        int l = 0, r = b.size() - 1;
        while (r - l > 2) {
            int m1 = (r + l) / 2;
            int m2 = m1 + 1;
            if (f(m1, x) <= f(m2, x)) {
                l = m2;
            } else {
                r = m2;
            }
           // cout << l << ' ' << r << endl;
        }

        cout << min({f(l, x), f(l + 1, x), f(min(r, (int)b.size() - 1), x)}) << ' ';
        //cout << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}