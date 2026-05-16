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
    int mx = 0;
    int cnt = 0;
    vector<int> ks(q);
    vector<int> result(q, n);
    for (auto& i : ks) cin >> i;
    for (auto& i : scanpoint) {
        cnt++;
        value += i.second;
        for (int j = 0; j < q; j++) {
            if (min(cnt, (2 * n - cnt)) >= ks[j]) {
                int dop = 2 * value - cnt;
                int need = ks[j] - dop;
                need += need % 2;
                need /= 2;
                result[j] = min(result[j], max(static_cast<int>(0), need));
            }
        }
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