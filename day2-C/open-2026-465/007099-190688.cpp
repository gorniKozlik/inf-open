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
    }
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (ev[i].second == 1) {
            ++suf_l[i];
        }
        if (i < 2 * n - 1) {
            suf_l[i] += suf_l[i + 1];
        }
    }
    vector<int> reqs(q), ans(q, inf);
    for (int &i: reqs) { cin >> i; }
    int cnt = 0;
    for (int i = 0; i < n * 2 - 1; ++i) {
        if (i == 2) {
            int dgfg = 2;
        }
        cnt += ev[i].second;
        if (ev[i + 1].first == ev[i].first) { continue; }

        int lb = -1, rb = i, mid;
        while (rb - lb > 1) {
            mid = (lb + rb) / 2;
            if (ev[mid].first <= ev[i].first) {
                lb = mid;
            } else {
                rb = mid;
            }
        }
        int prev_r = lb;
        lb = i, rb = 2 * n;
        while (rb - lb > 1) {
            mid = (lb + rb) / 2;
            if (ev[mid].first >= ev[i].first) {
                rb = mid;
            } else {
                lb = mid;
            }
        }
        int next_l = rb;
        vector<int> cur_an(n + 1, inf);
        int did = 0;
        int total = cnt;
        cur_an[total] = 0;
        bool flag = false;
        int p1 = 0;
        if (prev_r != -1) { p1 = pref_r[prev_r]; }
        int p2 = 0;
        if (next_l != 2 * n) { p2 = suf_l[next_l]; }
        while (p1 && p2) {
            ++did;
            total += 2;
            --p1;
            --p2;
            cur_an[total] = min(cur_an[total], did);
        }
        int fake_cnt = cnt;
        if (!flag) {
            while (fake_cnt && p1) {
                --p1;
                ++did;
                ++total;
                --fake_cnt;
                cur_an[total] = min(cur_an[total], did);
            }
            while (fake_cnt && p2) {
                --p2;
                ++did;
                ++total;
                --fake_cnt;
                cur_an[total] = min(cur_an[total], did);
            }
        }
        int val = inf;
        for (int j = n; j >= 0; --j) {
            val = min(val, cur_an[j]);
            cur_an[j] = val;
        }
        for (int j = 0; j < q; ++j) {
            ans[j] = min(ans[j], cur_an[reqs[j]]);
        }
    }
    for (int i: ans) { cout << i << ' '; }
}
