#include <bits/stdc++.h>
#define int long long
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define em emplace_back

using namespace std;
template<class C>
using vec = vector<C>;
using vi = vector<int>;
using pii = pair<int, int>;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vi l(n), r(n);
    vi b;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        b.pb(l[i]);
        b.pb(r[i]);
    }
    sort(all(b));
    int best = -1;
    int mx = LLONG_MIN;
    vec<pii> f(b.size());
    for (int j = 0; j < b.size(); j++) {
        int p = b[j];
        int cntl = 0, cntr = 0, in = 0;
        for (int i = 0; i < n; i++) {
            if (r[i] < p) {
                cntl++;
            }
            if (p < l[i]) {
                cntr++;
            }
            if (l[i] <= p && p <= r[i]) {
                in++;
            }
        }
        if (min(cntl, cntr) > mx) {
            mx = min(cntl, cntr);
            best = j;
        }
        f[j] = make_pair(in, min(cntl, cntr));
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int ans = LLONG_MAX;
        for (int j = max(0ll, best - 3); j < min((int)b.size(), best + 3); j++) {
            int ost = k;
            int d = 0;
            ost -= f[j].first;
            if (ost > 0) {
                int make = min((ost + 1) / 2, f[j].second);
                ost -= 2 * make;
                d += make;
            }
            if (ost > 0) {
                d += ost;
            }
            ans = min(ans, d);
        }
        cout << ans << ' ';
    }
}