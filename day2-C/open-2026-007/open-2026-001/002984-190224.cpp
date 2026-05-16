#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 210000;
const int INF = (int)(1e18);

int n, q, l[N], r[N], f[N];
vector<array<int, 2>> vec;

void upd(int cnt, int left) {
    int add = min(left, n - cnt - left);
    cout << add << endl;
    f[cnt + 2 * add] = min(f[cnt + 2 * add], add);
    f[cnt + 2 * add - 1] = min(f[cnt + 2 * add - 1], add);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        f[i] = +INF;
        cin >> l[i] >> r[i];
        vec.push_back({l[i], +1});
        vec.push_back({r[i], -1});
    }
    sort(begin(vec), end(vec));
    int cnt = 0, left = 0;
    for (auto [u, v] : vec) {
        upd(cnt, left);
        if (v == +1) cnt++;
        upd(cnt, left);
        if (v == -1) {
            cnt--;
            left++;
        }
        upd(cnt, left);
    }
    for (int i = n; i >= 2; i--)
        f[i - 2] = min(f[i - 2], f[i] - 1);
    for (int i = 1; i <= n; i++)
        f[i] = max(f[i], 0ll);
    for (int i = 1; i <= q; i++) {
        int k; cin >> k;
        cout << f[k] << ' ';
    }
}