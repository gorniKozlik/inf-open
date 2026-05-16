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
    vector<int> w(q);
    multiset<pair<int, int>> lol;
    map<pair<int, int>, int> cnt_used;
    for (int i = 0; i < n; i++) {
        lol.insert(a[i]);
        cnt_used[a[i]]++;
    }
    for (int i = 0; i < q; i++) {
        cin >> w[i];
    }
    int left = 0, right = n - 1;
    vector<int> res(n + 1, INFi);
    map<pair<int, int>, int> used;

    res[get(n, lol)] = 0;
    for (int tt = 0; tt < n && left < n && right >= 0; tt++) {
        while ((left < n && used[a[left]] == cnt_used[a[left]]) || left == right) {
            left++;
        }
        while ((right >= 0 && used[b[right]] == cnt_used[b[right]]) || left == right) {
            right--;
        }
        //cout << tt << ' ' << left << ' ' << right << endl;
        if (left < n && right >= 0) {
            used[a[left]]++;
            used[b[right]]++;
            /*for (auto j : lol) {
                cout << j.first << ' ' << j.second << '\n';
            }
            cout << "looooooooooooooooooooooooooooooooooooooooooooooooooooooooool\n";*/
            lol.erase(a[left]);
            lol.erase(b[right]);
            int nl1 = a[left].first;
            int nr1 = b[right].second;
            int nl2 = a[left].second;
            int nr2 = b[right].first;
            lol.insert({nl1, nr1});
            lol.insert({nl2, nr2});
            /*for (auto j : lol) {
                cout << j.first << ' ' << j.second << '\n';
            }
            cout << "-----------------------------------\n";*/
        }
        int rr = get(n, lol);
        res[rr] = min(res[rr], tt + 1);
    }
    /*for (auto i : lol) {
        cout << i.first << ' ' << i.second << '\n';
    }
    cout << '\n';*/
    for (int i = n - 1; i >= 0; i--) {
        res[i] = min(res[i], res[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        cout << res[w[i]] << ' ';
    }
    cout << '\n';
}
