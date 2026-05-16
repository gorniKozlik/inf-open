#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#pragma GCC target("avx2")
using ll = long long;

#define int ll

using namespace std;
const int mod = 998244353;
struct Mint {
    int val;
    Mint() {
        val = 0;
    }
    Mint(int x) {
        x %= mod;
        if (x < 0) x += mod;
        val = x;
    }
};
Mint operator+=(Mint& a, Mint b) {
    a.val += b.val;
    if (a.val >= mod) a.val -= mod;
    return a;
}
Mint operator-=(Mint& a, Mint b) {
    a.val -= b.val;
    if (a.val < 0) a.val += mod;
    return a;
}
Mint operator+(Mint a, Mint b) {
    a += b;
    return a;
}
Mint operator-(Mint a, Mint b) {
    a -= b;
    return a;
}
Mint operator*=(Mint& a, Mint b) {
    a.val = 1ll * a.val * b.val % mod;
    return a;
}
Mint operator*(Mint a, Mint b) {
    a *= b;
    return a;
}
Mint binpow(Mint x, int p) {
    if (p == 0) return 1;
    if (p == 1) return x;
    if (p % 2 == 0) {
        return binpow(x * x, p / 2);
    }
    return x * binpow(x, p - 1);
}

struct Event {
    int x, t, ind;
    bool operator<(Event& other) {
        return x < other.x || x == other.x && t < other.t;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    vector<int> k(q);
    for (int i = 0; i < q; i++) cin >> k[i];
    vector<Event> events;
    for (int i = 0; i < n; i++) {
        events.push_back({l[i], 0, i});
        events.push_back({r[i], 1, i});
    } 
    vector<int> sl = l, sr = r;
    sort(sl.begin(), sl.end());
    sort(sr.begin(), sr.end());
    sort(events.begin(), events.end());
    vector<int> curs, mins, maxs;
    int cur = 0;
    int res = 1e18;
    for (Event e : events) {
        int x = e.x;
        int t = e.t;
        int right = lower_bound(sr.begin(), sr.end(), x) - sr.begin();
        int left = upper_bound(sl.begin(), sl.end(), x) - sl.begin();
        left = n - left;
        int ind = e.ind;
        if (t == 0) {
            cur++;
            
        } else {
            cur--;
        }
        curs.push_back(cur);
        maxs.push_back(max(left, right));
        mins.push_back(min(left, right));
        // int delta = kk - cur;
        // if (delta <= 0) {
        //     res = 0;
        //     break;
        // }
        // int need2 = delta / 2;
        // int cnt2 = min(left, right);
        // delta -= min(need2, cnt2);
        // res = min(res, delta);
        // if (t == 0) {
            // cur++;
            // res = min(res, max(left, right));
        // }
    }
    int masum = -1e18;
    int macur = -1;
    int mamin = -1;
    for (int i = 0; i < curs.size(); i++) {
        if (curs[i] + mins[i] > masum && curs[i] > macur) {
            macur = curs[i];
            masum = mins[i] + curs[i];
            mamin = mins[i];
        }
        // masum = max(masum, curs[i] + mins[i]);
    }
    for (int i = 0; i < q; i++) {
        int kk = k[i];
        int res = 1e18;
        for (int j = 0; j < curs.size(); j++) {
            int delta = kk - curs[j];
            if (delta <= 0) {
                res = 0;
                break;
            }

            int need2 = delta / 2;
            int cnt2 = mins[j];
            delta -= min(need2, cnt2);
            res = min(res, delta);
        }
        cout << res << " ";
        
    }
        
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t --> 0) solve();
}