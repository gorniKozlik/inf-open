#include <experimental/random>
#include <bits/stdc++.h>

using namespace std;
//experimental::randint(1, 10);
#define ll long long

ll MOD = 998244353;
ll INF = 1e18;
//
// ll step(ll v,ll ind) {
//     if (ind == 0) {
//         return 1;
//     }
//     if (ind % 2 == 0) {
//         ll x = step(v, ind / 2);
//         return (x * x);
//     }
//     return (step(v, ind - 1) * v);
// }

bool cmp(pair<ll,ll> a, pair<ll,ll> b) {
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, q;
    cin >> n >> q;
    vector<pair<ll,ll> > s(n);
    for (ll i = 0; i < n; i++) {
        cin >> s[i].first >> s[i].second;
    }
    sort(s.begin(), s.end(), cmp);
    set<ll> st;
    ll ans0 = 0;
    vector<ll> answer(n + 1, INF);
    for (ll i = n - 1; i >= 0; i--) {
        while (!st.empty() && *st.rbegin() > s[i].second) {
            st.erase(*st.rbegin());
        }
        ll cnt = st.size() + 1;
        ans0 = max(ans0, cnt);
        ll vr = n - i - cnt;
        ll vl = i;
        ll d = min(vr, vl);
        for (ll j = 0; j <= d; j++) {
            answer[j * 2 + cnt] = min(answer[j * 2 + cnt], j);
        }
        if (vr > vl) {
            answer[d * 2 + cnt + 1] = min(answer[d * 2 + cnt + 1], d + 1);
        }
        st.insert(s[i].first);
    }
    st.clear();
    sort(s.begin(), s.end());
    for (ll i = 0; i < n; i++) {
        while (!st.empty() && *st.begin() < s[i].first) {
            st.erase(*st.begin());
        }
        ll cnt = st.size() + 1;
        ans0 = max(ans0, cnt);
        ll vr = n - 1 - i;
        ll vl = i - cnt;
        ll d = min(vr, vl);
        for (ll j = 0; j <= d; j++) {
            answer[j * 2 + cnt] = min(answer[j * 2 + cnt], j);
        }
        if (vr < vl) {
            answer[d * 2 + cnt + 1] = min(answer[d * 2 + cnt + 1], d + 1);
        }
        st.insert(s[i].second);
    }
    answer[ans0] = 0;
    for (ll i = n - 1; i >= 0; i--) {
        answer[i] = min(answer[i], answer[i + 1]);
    }
    vector<ll> qq(q);
    for (ll ii = 0; ii < q; ii++) {
        cin >> qq[ii];
        cout << answer[qq[ii]] << " ";
    }
}
