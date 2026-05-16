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
    }
    sort(all(b));
    vec<pii> f;
    for (auto& p : b) {
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
        f.em(in, min(cntl, cntr));
    }
    map<int, int> ff;
    for (int i = 0; i < f.size(); i++) {
        ff[f[i].first] = max(ff[f[i].first], f[i].second);
    }
    f.clear();
    int mxf = 0;
    for (auto& [i,j] : ff) {
        f.em(i, j);
        mxf = max(mxf, i);
    }
    sort(all(f), [&](pii i, pii j) {
        int vali = i.first + 2 * i.second;
        int valj = j.first + 2 * j.second;
        return vali < valj;
    });
    vi pref(f.size());
    for (int i = 0; i < f.size(); i++) {
        pref[i] = f[i].second + f[i].first;
        if (i)
            pref[i] = max(pref[i - 1], pref[i]);
    }
    vi suf(f.size());
    for (int i = (int)f.size() - 1; i >= 0; i--) {
        suf[i] = f[i].first;
        if (i + 1 < f.size())
            suf[i] = max(suf[i], suf[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int ans = LLONG_MAX;
        if (mxf >= k) {
            ans = 0;
        } else {
            int ll = -1, rr = f.size();
            while (ll + 1 < rr) {
                int mid = (ll + rr) >> 1;
                if (f[mid].second <= (k - f[mid].first) / 2) {
                    ll = mid;
                } else {
                    rr = mid;
                }
            }
            if (ll >= 0)
                ans = min(ans, k - pref[ll]);
            if (rr < f.size())
                ans = min(ans, k - suf[rr] - (k - suf[rr]) / 2);
        }
        cout << ans << ' ';
    }
}