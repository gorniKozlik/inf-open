#include <bits/stdc++.h>
using namespace std;
#define print(a) for (auto i : a) cout << i << " "; cout << "\n";
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;

int main() {
    // freopen("C:/work/untitled/input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<pl> a(n);
    for (int i = 0; i  <n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    while (q--) {
        int k; cin >> k;
        cout << k/2 << " ";
    }
}