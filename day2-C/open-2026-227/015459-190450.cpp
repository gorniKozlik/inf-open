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
void solve1(int n, int q) {
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
    for (int i = 0; i < q; i++) {
        int kk = k[i];
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
            int delta = kk - cur;
            if (delta <= 0) {
                res = 0;
                break;
            }
            int need2 = delta / 2;
            int cnt2 = min(left, right);
            delta -= min(need2, cnt2);
            res = min(res, delta);
            // if (t == 0) {
                // cur++;
                // res = min(res, max(left, right));
            // }
        }
        cout << res << " ";
    }
        
}
void solve() {
    int n, q; cin >> n >> q;
    if (n <= 3000) {
        solve1(n, q);
        return;
    }
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
    // for (int i : mins) cout << i << " ";
    // cout << "\n";
    int masum0 = -1e18;
    int macur0 = -1;
    int mamin0 = -1;
    int masum1 = -1e18;
    int macur1 = -1;
    int mamin1 = -1;

    int masum01 = -1e18;
    int macur01 = -1;
    int mamin01 = -1;
    int masum11 = -1e18;
    int macur11 = -1;
    int mamin11 = -1;

    int masum02 = -1e18;
    int macur02 = -1;
    int mamin02 = -1;
    int masum12 = -1e18;
    int macur12 = -1;
    int mamin12 = -1;

    int masum03 = -1e18;
    int macur03 = -1;
    int mamin03 = -1;
    int masum13 = -1e18;
    int macur13 = -1;
    int mamin13 = -1;

    for (int i = 0; i < curs.size(); i++) {
        if (curs[i] % 2 == 0) {
            if (curs[i] + mins[i] > masum0 || curs[i] + mins[i] == masum0 && curs[i] > macur0) {
                macur0 = curs[i];
                masum0 = mins[i] + curs[i];
                mamin0 = mins[i];
            }
        } else {
            if (curs[i] + mins[i] > masum1 || curs[i] + mins[i] == masum1 && curs[i] > macur1) {
                macur1 = curs[i];
                masum1 = mins[i] + curs[i];
                mamin1 = mins[i];
            }
        }
        if (curs[i] % 2 == 0) {
            if (curs[i] > macur01 || curs[i] == macur01 && mins[i] > mamin01) {
                macur01 = curs[i];
                masum01 = mins[i] + curs[i];
                mamin01 = mins[i];
            }
        } else {
            if (curs[i] > macur11 || curs[i] == macur11 && mins[i] > mamin11) {
                macur11 = curs[i];
                masum11 = mins[i] + curs[i];
                mamin11 = mins[i];
            }
        }

        if (curs[i] % 2 == 0) {
            if (mins[i] > mamin02 || mins[i] == mamin02 && curs[i] > macur02) {
                macur02 = curs[i];
                masum02 = mins[i] + curs[i];
                mamin02 = mins[i];
            }
        } else {
            if (mins[i] > mamin12 || mins[i] == mamin12 && curs[i] > macur12) {
                macur12 = curs[i];
                masum12 = mins[i] + curs[i];
                mamin12 = mins[i];
            }
        }
        if (curs[i] % 2 == 0) {
            if (curs[i] + mins[i] > masum03 || curs[i] + mins[i] == masum03 && mins[i] > mamin03) {
                macur03 = curs[i];
                masum03 = mins[i] + curs[i];
                mamin03 = mins[i];
            }
        } else {
            if (curs[i] + mins[i] > masum13 || curs[i] + mins[i] == masum13 && mins[i] > mamin13) {
                macur13 = curs[i];
                masum13 = mins[i] + curs[i];
                mamin13 = mins[i];
            }
        }
        
        // masum = max(masum, curs[i] + mins[i]);
    }
    // cout << macur0 << " " << mamin0 << " " << masum0 << "\n";
    // cout << macur1 << " " << mamin1 << " " << masum1 << "\n\n";
    // return;
    for (int i = 0; i < q; i++) {
        int kk = k[i];
        int res = 1e18;
        
        if (macur0 >= 0) {
            int delta = kk - macur0;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin0;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur1 >= 0) {
            int delta = kk - macur1;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin1;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur01 >= 0) {
            int delta = kk - macur01;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin01;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur11 >= 0) {
            int delta = kk - macur11;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin11;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur02 >= 0) {
            int delta = kk - macur02;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin02;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur12 >= 0) {
            int delta = kk - macur12;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin12;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur03 >= 0) {
            int delta = kk - macur03;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin03;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        if (macur13 >= 0) {
            int delta = kk - macur13;
            if (delta <= 0) {
                cout << 0 << " ";
                continue;
            }
            int need2 = delta / 2;
            int cnt2 = mamin13;
            delta -= min(need2, cnt2);
            res = min(res, delta);
        } 
        cout << res << " ";
        
        // int delta = kk - macur;
        // if (delta <= 0) {
        //     cout << 0 << " ";
        //     continue;
        // }
        // int need2 = delta / 2;
        // int cnt2 = mamin;
        // delta -= min(need2, cnt2);
        // cout << delta << " ";
    }
    // cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t --> 0) solve();
}