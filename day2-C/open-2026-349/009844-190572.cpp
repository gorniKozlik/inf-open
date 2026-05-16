#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
using vint = vector<int>;
using pii = pair<int, int>;
using vpii = vector<pii>;
constexpr int INF = 1 << 30;

bool cmp(pii a, pii b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int Func1(int k,int mx,int p,int n) {
    if (k <= mx) {
        return 0;
    }
    int a = p, b = n - p - mx;
    if (a < b) {
        swap(a, b);
    }
    int u = k;
    k -= mx;
    if (k <= 2 * b) {
        return k / 2 + k % 2;
    }
    int ans = b;
    a -= b;
    return ans + k - 2 * b;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vpii v;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v.emplace_back(a, 1);
        v.emplace_back(b, -1);
    }
    sort(v.begin(), v.end());
    int cnt = 0, mx = 0, pnow = 0, p = 0, a1 = 0;
    for (auto [x,t]: v) {
        cnt += t;
        if (t == -1) {
            pnow++;
        }
        if (cnt > mx || (cnt == mx && min(pnow, (n - pnow - mx)) > min(p, (n - p - mx)))) {
            mx = cnt;
            p = pnow;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        int ans1 = Func1(k, mx, p, n);
        cout << min(ans1, (n - 1) / 2 + (n - 1) % 2) << ' ';
    }
}
