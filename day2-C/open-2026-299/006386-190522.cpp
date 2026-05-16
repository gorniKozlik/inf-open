#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Event {
    int pos, t, i; // t=0 - open, t=1 - close
};
bool operator<(const Event& a, const Event& b) {
    if (a.pos != b.pos) return a.pos < b.pos;
    if (a.t != b.t) return a.t < b.t;
    return a.i < b.i;
}

int main() {
    #ifdef LOCAL
    freopen("_test.in", "r", stdin);
    freopen("_test.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    vector<Event> events;
    for (int i = 0; i < n; i++) {
        events.push_back({l[i], 0, i});
        events.push_back({r[i], 1, i});
    }
    sort(events.begin(), events.end());

    while (q--) {
        int k;
        cin >> k;

        if (k == 0) {
            cout << 0 << ' ';
            continue;;
        }

        int res = k / 2 + k % 2;
        cout << res << ' ';
    }
}