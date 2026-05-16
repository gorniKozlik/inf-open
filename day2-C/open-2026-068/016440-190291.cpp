#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

#define all(v) v.begin(), v.end()
#define rep(i, n) for (int i = 0; i < n; i++)
#define cin(v) for (auto& vi : v) { cin >> vi; }
#define cout(v) for (auto& vi : v) { cout << vi << ' '; } cout << '\n';
#define int long long

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;

const int INF = 1e9 + 7;
const int MOD = 998244353;
const int MOD2 = 1e9 + 737373;
const ll LINF = 1e18 + 7;
const double eps = 1e-8;
const double PI = acos(-1);

int n, m;

int ans[200073];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(10);
    bool g3 = 1;
    int q;
    cin >> n >> q;
    vector <pair <int, int> > segs(n);
    vector <pair <int, char> > space;
    rep(i, n) {
        cin >> segs[i].first >> segs[i].second;
        space.emplace_back(segs[i].first, 'L');
        space.emplace_back(segs[i].second, 'R');
    }
    sort(all(space));
    for (int i = 0; i < space.size() - 1; i++) {
        if (space[i].first == space[i + 1].first || space[i].second == space[i + 1].second) {
            g3 = 0;
            break;
        }
    }
    if (g3) {
        while (q--) {
            int k;
            cin >> k;
            cout << k / 2 << '\n';
        }
    }
    else if (true) {
        int KOL = -INF, MX = -INF;
        fill(ans, ans + n + 1, INF);
        int ls = 0, rs = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (space[i].second == 'L') {
                ls++;
                int mx = min(ls + rs, 2 * n - ls - rs);
                int kol = ls - rs;
                //cout << "L no " << ls + 1 << '\n';
                if (kol > KOL || mx > MX) {
                    for (int k = 1; k <= mx; k++) {
                        if (k <= kol) {
                            ans[k] = 0;
                            //cout << k << " : " << 0 << '\n';
                        }
                        else {
                            ans[k] = min(ans[k], (k - kol + 1) / 2);
                            //cout << k << " : " << min(ans[k], k - kol) << '\n';
                        }
                    }
                    KOL = max(KOL, kol);
                    MX = max(MX, mx);
                }
            }
            else {
                int mx = min(ls + rs + 1, 2 * n - ls - rs - 1);
                int kol = ls - rs;
                //cout << "R no " << rs + 1 << '\n';
                if (kol > KOL || mx > MX) {
                    for (int k = 1; k <= mx; k++) {
                        if (k <= kol) {
                            ans[k] = 0;
                            //cout << k << " : " << 0 << '\n';
                        }
                        else {
                            ans[k] = min(ans[k], (k - kol + 1) / 2);
                            //cout << k << " : " << min(ans[k], k - kol) << '\n';
                        }
                    }
                    KOL = max(KOL, kol);
                    MX = max(MX, mx);
                }
                rs++;
            }
        }
        while (q--) {
            int k;
            cin >> k;
            cout << ans[k] << '\n';
        }
    }
    else if (q == 1) {
        int k;
        cin >> k;
        if (k == n) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (space[i].second == 'R') {
                    cnt++;
                }
            }
            cout << cnt << '\n';
        }
        if (k <= 10) {
            fill(ans, ans + n + 1, INF);
            int ls = 0, rs = 0;
            for (int i = 0; i < 2 * n; i++) {
                if (space[i].second == 'L') {
                    ls++;
                    int mx = min(ls + rs, 2 * n - ls - rs);
                    int kol = ls - rs;
                    //cout << "L no " << ls + 1 << '\n';
                    for (int k = 1; k <= min(mx, 10LL); k++) {
                        if (k <= kol) {
                            ans[k] = 0;
                            //cout << k << " : " << 0 << '\n';
                        }
                        else {
                            ans[k] = min(ans[k], (k - kol + 1) / 2);
                            //cout << k << " : " << min(ans[k], k - kol) << '\n';
                        }
                    }
                }
                else {
                    int mx = min(ls + rs + 1, 2 * n - ls - rs - 1);
                    int kol = ls - rs;
                    //cout << "R no " << rs + 1 << '\n';
                    for (int k = 1; k <= min(mx, 10LL); k++) {
                        if (k <= kol) {
                            ans[k] = 0;
                            //cout << k << " : " << 0 << '\n';
                        }
                        else {
                            ans[k] = min(ans[k], (k - kol + 1) / 2);
                            //cout << k << " : " << min(ans[k], k - kol) << '\n';
                        }
                    }
                    rs++;
                }
            }
            cout << ans[k] << '\n';
        }
    }
    return 0;
}