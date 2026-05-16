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

struct SegmentTree {
    int size;
    struct Node {

    };
};

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
    vector<int> coord;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        coord.push_back(a[i].first);
        coord.push_back(a[i].second);
    }
    vector<int> w(q);
    for (int i = 0; i < q; i++) {
        cin >> w[i];
    }
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
    int len = (int)coord.size();
    map<pair<int, int>, int> cnt_used, used;
    for (int i = 0; i < n; i++) {
        a[i].first = lower_bound(coord.begin(), coord.end(), a[i].first) - coord.begin();
        a[i].second = lower_bound(coord.begin(), coord.end(), a[i].second) - coord.begin();
        cnt_used[a[i]]++;
    }

    vector<pair<int, int>> min_left = a, max_right = a;
    sort(min_left.begin(), min_left.end());
    sort(max_right.begin(), max_right.end(), cmp);

    vector<int> sum(len);
    for (int i = 0; i < n; i++) {
        for (int j = a[i].first; j <= a[i].second; j++) {
            sum[j]++;
        }
    }
    //cout << 777 << endl;
    vector<int> res(n + 1, INFi);
    int mx = 0;
    for (int j = 0; j < len; j++) {
        mx = max(mx, sum[j]);
    }
    res[mx] = 0;
    int left = 0, right = n - 1, tt = 0;
    for (; left < n && right >= 0;) {
        //cout << left << ' ' << right << endl;
        while (left < n && cnt_used[min_left[left]] == used[min_left[left]]) {
            left++;
        }
        if (left < n) {
            used[min_left[left]]++;
        }
        while (right >= 0 && cnt_used[max_right[right]] == used[max_right[right]] || left == right) {
            right--;
        }
        if (right >= 0) {
            used[max_right[right]]++;
        }
        //cout << left << ' ' << right << endl;
        if (left < n && right >= 0) {
            for (int j = min_left[left].first; j <= min_left[left].second; j++) {
                sum[j]--;
            }
            for (int j = max_right[right].first; j <= max_right[right].second; j++) {
                sum[j]--;
            }
            int nl1 = min_left[left].first;
            int nr1 = max_right[right].second;
            int nl2 = min_left[left].second;
            int nr2 = max_right[right].first;
            //cout << nl1 << ' ' << nr1 << ' ' << nl2 << ' ' << nr2 << endl;
            for (int j = nl1; j <= nr1; j++) {
                sum[j]++;
            }
            for (int j = nl2; j <= nr2; j++) {
                sum[j]++;
            }
        }
        mx = 0;
        for (int j = 0; j < len; j++) {
            mx = max(mx, sum[j]);
        }
        res[mx] = min(res[mx], ++tt);
    }
    for (int i = n - 1; i >= 1; i--) {
        res[i] = min(res[i], res[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        cout << res[w[i]] << ' ';
    }
    cout << '\n';
}
