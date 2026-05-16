#include <bits/stdc++.h>
using namespace std;


#define int long long
#define line cout << "\n"
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define sz(a) (int) a.size()
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pii pair<int, int>

typedef string str;
typedef long long ll;
typedef long double ld;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    vector<int> pt;
    for (auto &u : a) {
        cin >> u.first >> u.second;
        pt.pb(u.first);
        pt.pb(u.second);
    }
    vector<int> ans(n + 1, 1e18);
    sort(all(pt));
    for (auto &e : pt) {
        int cnt_good = 0;
        int cnt_left = 0, cnt_right = 0;
        int bad_eql_left = 0, bad_egl_right = 0;
        for (auto &u : a) {
            if (u.first <= e && e <= u.second) {
                cnt_good++;
            }
            if (u.second < e) {
                cnt_left++;
            } else if (u.second == e) {
                bad_eql_left++;
            }
            if (u.first > e) {
                cnt_right++;
            } else if (u.first == e) {
                bad_egl_right++;
            }
        }
        ans[cnt_good] = 0;
        for (int i = 1; i <= min(cnt_left, cnt_right); i++) {
            ans[i * 2 + cnt_good] = i;
        }
        if (cnt_left < cnt_right) {
            for (int i = 1; i <= bad_eql_left && i + cnt_left <= cnt_right; i++) {
                ans[cnt_left * 2 + cnt_good + i] = cnt_left + i;
            }
        }
        if (cnt_right < cnt_left) {
            for (int i = 1; i <= bad_egl_right && i + cnt_right <= cnt_left; i++) {
                ans[cnt_right * 2 + cnt_good + i] = cnt_right + i;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i + 1], ans[i]);
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}