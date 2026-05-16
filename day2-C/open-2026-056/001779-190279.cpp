#include "iostream"
#include "algorithm"
#include "vector"
#include "queue"
using namespace std;
#define int long long
#define all(arr) arr.begin(), arr.end()
#define _lg(x) (63 - __builtin_clzll(x))
constexpr int maxn = 200'010;
constexpr int mod = 1'000'000'007;
int arr[maxn]{};
int mx[maxn]{};
void solve() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> lines;
    vector<int> lines_conpr;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        lines.emplace_back(a, b);
        lines_conpr.push_back(a);
        lines_conpr.push_back(b);
    }
    sort(all(lines_conpr));
    vector<pair<int, int>> scanpoint;
    for (auto& i : lines) {
        scanpoint.emplace_back(lower_bound(all(lines_conpr), i.first) - lines_conpr.begin(), 1);
        scanpoint.emplace_back(lower_bound(all(lines_conpr), i.second) - lines_conpr.begin(), 0);
    }
    sort(all(scanpoint));
    int value = 0;
    int cnt = 0;
    vector<pair<int, int>> ks(q);
    vector<int> result(q, 0);
    vector<int> dopp(n, 0);
    for (int i = 0; i < q; i++) {
        cin >> ks[i].first;
        ks[i].second = i;
    }
    for (auto& i : scanpoint) {
        cnt++;
        value += i.second;
        if (cnt != 2 * n) dopp[min(cnt, 2 * n - cnt) - 1] = max(dopp[min(cnt, 2 * n - cnt) - 1], 2 * value - cnt);
    }
    sort(all(ks), greater<pair<int, int>>());
    int cur_index = n;
    int curres = 0;
    for (int i = 0; i < q; i++) {
        while (cur_index >= ks[i].first) {
            cur_index--;
            curres = max(curres, dopp[cur_index]);
        }
        int need = ks[i].first - curres;
        need += need % 2;
        need /= 2;
        result[ks[i].second] = max(need, (int)0);
    }
    for (int i = 0; i < q; i++) {
        cout << result[i] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; //cin >> t;
    while (t--) {
        solve();
    }
}