#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

const int INF = 1e9;
int n;
vi lx, rx;

int f(int k, int x) {
    // cout << "Eqqq"  << endl;
    int cover = n - lx[x] - rx[x];
    int rest = k - cover;
    
    int val = 0;

    if (2 * min(lx[x], rx[x]) >= rest) {
        val += (rest + 1) / 2;
    } else {
        val += min(lx[x], rx[x]);
        val += rest - 2 * min(lx[x], rx[x]);
    }

    if (k > max(min(x + 1, 2 * n - (x + 1)), min(x, 2 * n - x))) return INF;

    return val;
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> n >> q;

    vi l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];

    vector<pi> events;
    vi ans(n + 1, 3 * n + 100);

    vi cords;
    for (int x : l) cords.pb(x);
    for (int x : r) cords.pb(x);

    sort(cords.begin(), cords.end());

    int sz = cords.size();

    for (int i = 0; i < sz; ++i) {
        int x = cords[i];

        int cnt = 0;

        int ls = 0;
        int rs = 0;

        int left1 = i;
        int left2 = i + 1;
        int right1 = sz - i;
        int right2 = sz - i - 1;


        for (int j = 0; j < n; ++j) {
            if ((l[j] <= x) && (x <= r[j])) ++cnt;
            if (r[j] < x) ++ls;
            else if (l[j] > x) ++rs;
        }

        int maxb = max(min(right1, left1), min(left2, right2));
        // ans[maxb] = min(ans[maxb], (int)0);
        ans[cnt] = min(ans[cnt], (int)0);
        int opers = 0;

        int curb = cnt;

        // cout << "maxbv " << i << ' ' << maxb << endl;
        // if (cnt >= 3) {
        //     cout << "AA " << i << endl;
        // }
        for (int b = cnt + 1; b <= maxb; ++b) {
            // if (b == 6) cout << "T" << endl;
            if (curb >= b) {
                ans[b] = min(ans[b], opers);
                continue;
            }

            if (min(ls, rs) > 0) {
                --ls;
                --rs;
                ++opers;
                curb += 2;
            } else {
                ++opers;
                ++curb;
            }

            // if (b == 3 && opers == 0) {
            //     cout << "AA " << i << ' ' << x << endl;
            // } 
            // if (b == 6) cout << "| " << endl;
            ans[b] = min(ans[b], opers);
        }
    }

    for (int i = n - 1; i >= 0; --i) ans[i] = min(ans[i + 1], ans[i]);

    for (int id = 0; id < q; ++id) {
        int k;
        cin >> k;

        cout << ans[k] << ' ';
    }
}