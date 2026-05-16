#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;
const ll inf = 1e18;
void solve();

template<typename T, typename T1> T remax(T& x, T1 y) { if (x < y) x = y; return x; }
template<typename T, typename T1> T remin(T& x, T1 y) { if (y < x) x = y; return x; }

int main() {
#ifdef BLOCKS
    freopen("input.txt", "r", stdin);
#endif // BLOCKS
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}
#define int int64_t

struct ev {
    int x, type, id;
    bool operator<(const ev& o) const {
        if (x != o.x) return x < o.x;
        return type < o.type;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<pair<int, int>> al;
    for (auto& [x, y] : a) {
        cin >> x >> y;
        al.emplace_back(x, 1);
        al.emplace_back(y, -1);
    }
    std::sort(al.begin(), al.end());
    for (auto& [l, r] : a) {
        l = std::lower_bound(al.begin(), al.end(), pair<int, int>(l, -1)) - al.begin();
        r = std::lower_bound(al.begin(), al.end(), pair<int, int>(r, -1)) - al.begin();
    }
//    vector<int> cnt(2 * n);
    int cur = 0, it = 0;
    int cntcl = 0, cntno = n;

    vector<pair<int, int>> z(2 * n);
//    vector<ev> event;
    vector<vector<pair<int, int>>> event(n + 1);
    vector<int> ans(n + 1, n);

    for (auto& [x, t] : al) {
        if (t == 1) cntno--;
        else cntcl++;
        cur += t;
//        cnt[it] = cur;
        int l = cur, r = cur + min(cntno, cntcl) * 2;
//        for (int i = l; i <= r; i += 2) {
//            remin(ans[i], (i - l) / 2);
//        }
        z[it] = {cur, cur + min(cntno, cntcl) * 2};
        event[l].emplace_back(-1, it);
        event[r].emplace_back(1, l);
        it++;
    }
    multiset<int> ms;
    for (int i = 1; i <= n; ++i) std::sort(event[i].begin(), event[i].end());
    for (int i = 1; i <= n; i += 2) {
        for (auto& [type, id] : event[i]) {
            if (type == 1) continue;
            ms.emplace(- i / 2);
        }
        if (!ms.empty()) remin(ans[i], *ms.begin() + i / 2);
        for (auto& [type, id] : event[i]) {
            if (type == -1) continue;
            ms.extract( - id / 2);
        }
    }
    ms.clear();
    for (int i = 0; i <= n; i += 2) {
        for (auto& [type, id] : event[i]) {
            if (type == 1) continue;
            ms.emplace(- i / 2);
        }
        if (!ms.empty()) remin(ans[i], *ms.begin() + i / 2);
        for (auto& [type, id] : event[i]) {
            if (type == -1) continue;
            ms.extract(- id / 2);
        }
    }
    for (int i = n - 1; i >= 1; --i) remin(ans[i], ans[i + 1]);
    while (q--) {
        int k; cin >> k;
        cout << ans[k] << ' ';
    }
}
