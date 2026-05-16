#include <bits/stdc++.h>
#include <random>

#define i128 __int128
#define int long long
#define set unordered_set

using namespace std;

random_device lal;
mt19937 rnd(lal());


const int inf = 1e18, mod = 998'244'353;


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > ev;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        ev.push_back({l, 1});
        ev.push_back({r + 1, -1});
    }
    sort(ev.begin(), ev.end());
    vector<int> pref_r(2 * n), suf_l(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        if (ev[i].second == -1) {
            pref_r[i]++;
        }
        if (i > 0) { pref_r[i] += pref_r[i - 1]; }
        if (ev[i].second == 1) {
            ++suf_l[i];
        }
        if (i < 2 * n - 1) {
            suf_l[i] += suf_l[i + 1];
        }
    }
    vector<int> reqs(q);
    for (int &i: reqs) { cin >> i; }
    vector<int> ans(q, inf);
    int cnt = 0;
    for (int i = 0; i < n * 2 - 1; ++i) {
        cnt += ev[i].second;
        if (ev[i + 1].first == ev[i].first) { continue; }
        for (int j = 0; j < q; ++j) {
            ans[j] = min(ans[j], max(reqs[j] - cnt, (int) 0));
        }
    }
    for (int i: ans) { cout << i << ' '; }
}
