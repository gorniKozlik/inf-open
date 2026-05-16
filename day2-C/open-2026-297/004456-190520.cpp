#include <bits/stdc++.h>

#define all(a) a.begin(), a.end()
#define pb push_back
#define lb lower_bound

using ll = long long;
using namespace std;

const int mod = 998244353;
const ll inf = 1e18;
const int k = 475;

struct event {
    int x, type;
    bool operator<(const event f) const {
        return tie(x, type) < tie(f.x, f.type);
    }
};

void read() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

int main() {
    read();

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
    }

    vector<int> ans(n + 1), query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i];
    }

    set<pair<int, int>> R; set<pair<int, int>, greater<>> L;
    for (int i = 0; i < n; i++) {
        L.insert({seg[i].first, i});
        R.insert({seg[i].second, i});
    }

    auto scanline = [&]() {
        vector<event> s;
        for (int i = 0; i < n; i++) {
            s.pb(event{seg[i].first, -1});
            s.pb(event{seg[i].second, 1});
        }

        sort(all(s));
        int cnt = 0, ans = 0;
        for (auto [x, type] : s) {
            cnt -= type;
            ans = max(ans, cnt);
        }

        return ans;
    };

    int j = 1, F = 0;
    while (j <= scanline()) {
        ans[j] = F;
        j++;
    }

    F++;

    while (j <= n) {
        int v = R.begin()->second,
            u = L.begin()->second;
        R.erase(R.begin());
        L.erase(L.begin());
        swap(seg[v].second, seg[u].first);
        int res = scanline();
        while (j <= res) {
            ans[j] = F;
            j++;
        }
        F++;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[query[i]] << " ";
    }

    cout << "\n";
}
