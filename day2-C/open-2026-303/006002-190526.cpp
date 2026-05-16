#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
using ll = long long;
using ld = long double;

const int maxn = 2e5 + 2;
const int inf = 1e9 + 1;

int l[maxn], r[maxn];

int k[maxn];

vector<pair<int, int>> v;

int ans[maxn];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i < n + 1; i++) {
        int l, r; cin >> l >> r;
        v.emplace_back(l, 0);
        v.emplace_back(r, 1);
    }
    for (int i = 1; i < q + 1; i++) {
        cin >> k[i];
    }
    for (int i = 1; i < q + 1; i++) {
        cout << k[i] / 2 << " ";
    }
}

