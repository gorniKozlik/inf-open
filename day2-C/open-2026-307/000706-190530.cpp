#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
#include <ctime>
#include <unordered_map>
#include <cmath>
#include <cstring>
#include <numeric>
#include <deque>

using namespace std;
using ll = long long;

class sgt_r {
    private:

    ll n;
    vector <ll> sg;
    vector <ll> d;
    ll sch;

    void update(int a) {
        sg[a] = max(max(sg[a*2+1], d[a*2+1]), max(sg[a*2+2], d[a*2+2]));
    }

    void push(int a) {
        d[a*2+1] = max(d[a], d[2*a+1]);
        d[a*2+2] = max(d[a], d[2*a+2]);
        d[a] = 0;
    }

    void chg(int a, ll l, ll r, ll li, ll ri, ll x) {
        if (r < li || l > ri) return;
        if (li <= l && r <= ri) {
            if (l == r) {
                sg[a] = max(sg[a], x);
            } else {
                d[a] = x;
            }
            return;
        }
        ll m = (l+r)/2;
        chg(a*2+1, l, m, li, ri, x); chg(a*2+2, m+1, r, li, ri, x);
        update(a);
    }

    ll get(int a, ll l, ll r, ll li, ll ri) {
        if (l > ri || r < li) return 0;
        if (li <= l && r <= ri) return max(sg[a], d[a]);
        ll m = (l+r)/2;
        push(a);
        update(a);
        return max(get(a*2+1, l, m, li, ri), get(a*2+2, m+1, r, li, ri));
    }

    public:

    sgt_r (ll n1) {
        n = n1;
        sg.resize(4*n+1000);
        d.resize(4*n+1000);
    }

    void change(ll l, ll r, ll val) {
        chg(0, 0, n-1, l, r, val);
    }

    ll get_ans(ll l, ll r) {
        return get(0, 0, n-1, l, r);
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    vector <pair <ll, ll>> pt;
    sgt_r dp(n);
    for (int i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        pt.push_back({a, 1});
        pt.push_back({b, -1});
    }
    sort(pt.begin(), pt.end());
    ll sch = 0;
    ll sch1 = 0;
    for (int i = 0; i < 2*n; ++i) {
        sch += pt[i].second;
        if (pt[i].second == -1) sch1++;
        cout << sch+min(sch1, n-sch-sch1)*2 << '\n';
        dp.change(0, sch+min(sch1, n-sch-sch1)*2, sch);
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << max((ll) 0, (k-dp.get_ans(k, k)+1)/2) << '\n';
    }
}