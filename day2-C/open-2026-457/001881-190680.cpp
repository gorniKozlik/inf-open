#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

const ll INF = (ll)1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    for (int i = 0; i < q; ++i) {
        int ki;
        cin >> ki;
        cout << ki / 2 << " ";
    }
    cout << "\n";
    return 0;
}