#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using ll = long long;
using ld = long double;

const int MOD = 998244353;
const int INFi = 1e9;
const ll INF = 1e18;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int bin_pow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) {
            res = res * 1ll * x % MOD;
        }
        y >>= 1;
        x = x * 1ll * x % MOD;
    }
    return res;
}

int get(int n, const multiset<pair<int, int>>& a) {
    int cur = 0, ans = 0;
    vector<pair<int, int>> b;
    for (auto i : a) {
        b.push_back({i.first, -1});
        b.push_back({i.second, 1});
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < n * 2; i++) {
        if (b[i].second == -1) {
            cur++;
        } else {
            cur--;
        }
        ans = max(ans, cur);
    }
    return ans;
}

bool cmp(pair<int, int>& x, pair<int, int>& y) {
    return x.second < y.second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    auto b = a;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), cmp);
    vector<pair<int, int>> w(q);
    multiset<pair<int, int>> lol;
    for (int i = 0; i < n; i++) {
        lol.insert(a[i]);
    }
    for (int i = 0; i < q; i++) {
        cin >> w[i].first;
        w[i].second = i;
    }
    sort(w.begin(), w.end());
    int left = 0, right = n - 1;
    map<int, int> res;
    map<pair<int, int>, int> used;
    vector<int> used2(n * 2);

    res[get(n, lol)] = 0;
    for (int tt = 0; tt < n && left < n && right >= 0; tt++) {
        while ((left < n && used[a[left]]) || left == right) {
            left++;
        }
        while ((right >= 0 && used[b[right]]) || left == right) {
            right--;
        }
        //cout << tt << ' ' << left << ' ' << right << endl;
        if (left < n && right >= 0) {
            used[a[left]] = 1;
            used[b[right]] = 1;
            lol.erase(lol.find(a[left]));
            lol.erase(lol.find(b[right]));
            int nl1 = a[left].first;
            int nr1 = b[right].second;
            int nl2 = a[left].second;
            int nr2 = b[right].first;
            lol.insert({nl1, nr1});
            lol.insert({nl2, nr2});
        }
        int rr = get(n, lol);
        if (!used2[rr]) {
            used2[rr] = 1;
            res[get(n, lol)] = tt + 1;
        }
    }
    vector<pair<int, int>> kek;
    for (auto i : res) {
        kek.push_back(i);
    }
    int len = (int)kek.size();
    for (int i = len - 2; i >= 0; i--) {
        kek[i].second = min(kek[i].second, kek[i + 1].second);
    }
    vector<int> ans(q);
    int cur = 0;
    for (auto i : kek) {
        while (cur < q && w[cur].first <= i.first) {
            ans[w[cur].second] = i.second;
            cur++;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
