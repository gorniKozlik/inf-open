#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e15;

struct node{
    ll l, r;
};

bool cmp (const node a, const node b){
    return a.l < b.l;
}

vector<pair<ll, ll>> vec;

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    ll n, q;
    cin >> n >> q;
    vector<node> v (n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].l >> v[i].r;
        vec.push_back({v[i].l, 1});
        vec.push_back({v[i].r, -1});
    }
    ll cnt = 0;
    sort(vec.begin(), vec.end());
    vector<pair<ll, ll>> dec;
    for (int i = 0; i < 2*n; ++i) {
        cnt += vec[i].second;
        ll d1 = (i - cnt + 1);
        ll d2 = (2*n - i - 1 - cnt);
        dec.push_back({min(d1, d2) + cnt, cnt});
    }
    sort(dec.begin(), dec.end());
    vector<ll> mx (2*n);
    for (int i = 2*n-1; i >= 0; --i) {
        mx[i] = dec[i].second;
        if (i != 2*n-1)
            mx[i] = max(mx[i], mx[i+1]);
    }
    for (int i = 0; i < q; ++i) {
        ll k;
        cin >> k;
        ll l = -1, r = 2*n;
        while (l+1 < r){
            ll m = (l+r)/2;
            if (dec[m].first >= k){
                r = m;
            }
            else
                l = m;
        }
        ll ans = (k - mx[r] + 1)/2;
        cout << max((ll)0, ans) << " ";
    }
}