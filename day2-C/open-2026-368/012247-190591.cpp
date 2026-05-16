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

enum class EventType { START, END };

struct Event {
    ll x;
    EventType type;
    Segment seg;

    bool operator<(const Event& other) const {
        return pair{x, type} < pair{other.x, other.type};
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<Segment> segs(n);
    vector<ll> reqs(q);
    vector<Event> events;
    cin >> segs >> reqs;

    for (auto& s : segs) {
        events.emplace_back(s.l, EventType::START, s);
        events.emplace_back(s.r, EventType::END, s);
    }

    sort(events.begin(), events.end());
    vector<ll> pts(2 * n + 1);

    ll bal = 0;
    for (ll i = 0; i < (ll)events.size(); i++) {
        auto& event = events[i];
        if (event.type == EventType::START) {
            bal++;
        } else {
            bal--;
        }

        ll cur_k = min(i + 1, 2 * n - i);
        pts[cur_k] = max(pts[cur_k], bal);
    }

    ll bst = -1;
    for (ll i = 2 * n; i >= 0; i--) {
        bst = max(pts[i], bst);
        pts[i] = bst;
    }

    for (ll& req : reqs) {
        cout << (max(0LL, req - pts[req]) + 1) / 2 << ' ';
    }
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
