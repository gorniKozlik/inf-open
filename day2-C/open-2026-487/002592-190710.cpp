#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll n, q;
vector<pair<ll, ll>> a;
vector<ll> b;

void input() {
    cin >> n >> q;
    a.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    b.resize(q);
    for (ll i = 0; i < q; i++) {
        cin >> b[i];
    }
}

void solve() {
    vector<pair<ll, ll>> x;
    for (ll i = 0; i < n; i++) {
        x.push_back({a[i].first, 1});
        x.push_back({a[i].second, 2});
    }
    sort(x.begin(), x.end());
    vector<ll> maxim(n + 1, 0);
    ll cnt = 0;
    for (ll i = 0; i < x.size(); i++) {
        if (x[i].second == 1) {
            cnt++;
        } else {
            cnt--;
        }
        //cout << cnt << " " << min(i + 1, 2 * n - i - 1) << "\n";
        maxim[min(i + 1, 2 * n - i - 1)] = max(maxim[min(i + 1, 2 * n - i - 1)], cnt);
    }
    for (ll j = n - 1; j > -1; j--) {
        maxim[j] = max(maxim[j + 1], maxim[j]);
    }
    for (ll i = 0; i < q; i++) {
        if (maxim[b[i]] >= b[i]) {
            cout << 0 << " ";
        } else {
            ll ost = b[i] - maxim[b[i]];
            cout << ost / 2 + ost % 2 << " ";
        }
    }
}

void output() {

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    solve();
    output();
    return 0;
}
