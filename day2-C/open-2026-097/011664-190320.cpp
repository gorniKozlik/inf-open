#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using uc = unsigned char;
using ull = unsigned long long;
using ul = unsigned long;
using i128 = __int128_t;
using u128 = __uint128_t;

ll MOD = 1e9 + 7;
ull P = 465828561843ULL;
ll LLINF = 1e18 + 100;
int INTINF = 1e9 + 100;

struct event {
    int pos;
    bool open;
};

inline void solve(ostringstream &os) {
    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> vec(n);
    vector<event> events;
    events.reserve(n * 2);
    for (auto& pr : vec) {
        cin >> pr.first >> pr.second;
        events.push_back({pr.first, true});
        events.push_back({pr.second, false});
    }

    sort(events.begin(), events.end(), [](const event& f, const event& s) -> bool {
        return f.pos != s.pos ? f.pos < s.pos : f.open > s.open;
    });

    sort(vec.begin(), vec.end());

    int cnt = 0;
    int mx = 0;
    int start_pos = -1;
    int end_pos = -1;

    vector<pair<int, int>> best;
    best.reserve(n);

    for (auto& ev: events) {
        if (ev.open) {
            cnt++;
            if (cnt > mx) {
                mx = cnt;
                start_pos = ev.pos;
                best.clear();
            }

            else if (cnt == mx) {
                start_pos = ev.pos;
            }
        }

        else {
            if (cnt == mx) {
                best.push_back({start_pos, end_pos});
            }

            cnt--;
        }
    }

    vector<int> l_border(n);
    vector<int> r_border(n);
    for (int i = 0; i < n; ++i) {
        auto& v = vec[i];
        l_border[i] = v.first;
        r_border[i] = v.second;
    }
    sort(l_border.begin(), l_border.end());
    sort(r_border.begin(), r_border.end());

    int ans = 0;
    for (auto& b : best) {
        int lefter = lower_bound(r_border.begin(), r_border.end(), b.first) - r_border.begin();
        int righter = l_border.end() - upper_bound(l_border.begin(), l_border.end(), b.second);

        ans = min(ans, max(lefter, righter));
    }


    for (int i = 0; i < q; ++i) {
        int amount = 0;
        cin >> amount;
        os << ans << ' ';
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ostringstream os;

    solve(os);

    cout << os.str();
    // exit(0);
}
