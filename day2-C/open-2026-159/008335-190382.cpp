#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using u128 = __int128_t;
using ull = unsigned long long;
using ld = long double;

#define dbg(x) cerr << #x << " = " << x << endl

const ll LINF = 2e18;
const int INF = 1e9 + 10;
const int LOG = 30;

const int N = 2e5 + 10;

struct event {
    int x, tp;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    vector<int> k(q);
    for (int &i : k) cin >> i;

    vector<event> events;
    for (int i = 0; i < n; i++) {
        events.push_back({l[i], 0});
        events.push_back({r[i], 1});
    }
    sort(events.begin(), events.end(), [](auto a, auto b){return a.x < b.x;});

    auto count = [](int db, int sng, int need) {
        if (db * 2 >= need) {
            return (need + 1) / 2;
        } else {
            return need - db * 2 + db;
        }
    };

    vector<int> ind(q);
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(), ind.end(), [&](auto a, auto b){return k[a] < k[b];});

    vector<int> ans(q, INF);
    int close = 0, open = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>> pq_main, pq_add;
    for (auto e : events) {
        if (e.tp == 0) open++;

        int left = close, right = n - open - close;
        int pairs = min(left, right);
        pq_main.push({open, pairs});
        if (e.tp == 0 && left - pairs == 1) {
            pq_add.push({open, pairs});
        }
        if (e.tp == 1 && right - pairs == 1) {
            pq_add.push({open, pairs});
        }

        if (e.tp == 1) {
            open--;
            close++;
        }
    }

    for (int i : ind) {
        while (!pq_main.empty()) {
            auto [open, pairs] = pq_main.top();
            int need = k[i] - open;
            if (pairs * 2 >= need) {
                ans[i] = min(ans[i], count(pairs, 0, need));
                break;
            }
            pq_main.pop();
        } 
        while (!pq_add.empty()) {
            auto [open, pairs] = pq_add.top();
            int need = k[i] - open;
            if (pairs * 2 + 1 >= need) {
                ans[i] = min(ans[i], count(pairs, 1, need));
                break;
            }
            pq_add.pop();
        }
    }

    for (int i : ans) cout << i << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed;
    cout.precision(9);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
