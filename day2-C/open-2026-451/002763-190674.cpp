#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll inf = 2e18;
const ld eps = 1e-13;
using vl = vector<ll>;
using vvl = vector<vl>;
struct tp {
    ll l, r;
};
struct Event {
    ll type, x, indx;
    bool operator <(const Event &e) const {
        if (x == e.x) return type > e.type;
        return x < e.x;
    }
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, q; cin >> n >> q;
    vector<tp> a(n);
    for (auto &i : a) cin >> i.l >> i.r;
    vector<ll> memo(n + 1, inf);
    memo[0] = 0;
    vector<Event> ev;
    for (ll i = 0; i < n; i++) {
        ev.push_back({1, a[i].l, i});
        ev.push_back({0, a[i].r, i});
    }
    sort(ev.begin(), ev.end());
    ll cnt = 0;
    ll maxx = 0;
    ll lmax = -1, rmax = -1;
    ll prev = -1;
    for (auto &i : ev) {
        if (i.type) cnt++;
        else cnt--;
        if (cnt > maxx) {
            lmax = prev;
            rmax = i.x;
        }
        prev = i.x;
        maxx = max(maxx, cnt);
    }
    for (ll i = 0; i <= maxx; i++) {
        memo[i] = 0;
    }
    ll cnt_left = 0;
    ll cnt_right = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i].r < lmax) cnt_left++;
        if (a[i].l > rmax) cnt_right++;
    }
    ll all = maxx;
    ll curr = 0;
    for (ll i = 0; i <= n; i++) {
        if (all >= i) {
            memo[i] = curr;
            continue;
        }
        if (cnt_left && cnt_right) {
            all += 2;
            curr++;
            cnt_left--;
            cnt_right--;
        } else {
            if (cnt_left) {
                cnt_left--;
                curr++;
                all++;
            } else {
                cnt_right--;
                curr++;
                all++;
            }
        }
        memo[i] = curr;
    }
    while (q--) {
        ll k; cin >> k;
        cout << memo[k] << " ";
    }
}
