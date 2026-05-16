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
vector<tp> a;
vector<ll> memo;
vector<Event> ev;
ll n, q;
void check(ll lmax, ll rmax, ll maxx) {
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
            memo[i] = min(memo[i], curr);
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
        memo[i] = min(memo[i], curr);
    }
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    a.resize(n);
    for (auto &i : a) cin >> i.l >> i.r;
    memo.assign(n + 1, inf);
    memo[0] = 0;
    for (ll i = 0; i < n; i++) {
        ev.push_back({1, a[i].l, i});
        ev.push_back({0, a[i].r, i});
    }
    sort(ev.begin(), ev.end());
    ll cnt = 0;
    ll prev = -1;
    for (auto &i : ev) {
        if (i.type == 1) cnt++;
        if (prev != -1) {
//            cout << prev << " " << i.x << " " << cnt << "\n";
            check(prev, i.x, cnt);
        }
        if (i.type == 0) cnt--;
        prev = i.x;
    }
    while (q--) {
        ll k; cin >> k;
        cout << memo[k] << " ";
    }
}

