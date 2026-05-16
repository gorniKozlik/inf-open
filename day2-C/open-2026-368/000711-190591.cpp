#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;

template <class T>
istream& operator>>(istream& in, vector<T>& a) {
    for (auto& l : a) in >> l;
    return in;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& a) {
    for (auto& l : a) out << l << ' ';
    return out;
}

struct Segment {
    ll l, r;

    friend istream& operator>>(istream& in, Segment& s) {
        in >> s.l >> s.r;
        return in;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<Segment> segs(n);
    vector<ll> reqs(q), pts;
    cin >> segs >> reqs;

    for (ll i = 0; i < n; i++) {
        pts.push_back(segs[i].l);
        pts.push_back(segs[i].r);
    }

    sort(pts.begin(), pts.end());

    ll ans = 1e18;
    for (ll pt : {pts[pts.size() / 2 - 1], pts[pts.size() / 2]}) {
        ll cnt = 0;
        for (auto& seg : segs) {
            if (seg.r < pts[pts.size() / 2] || seg.l > pts[pts.size() / 2]) {
                cnt++;
            }
        }
        ans = min(ans, (cnt + 1) / 2);
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
#ifdef LOCAL
    freopen("in_g.txt", "r", stdin);
    cin >> t;
#endif

    while (t--) solve();
}