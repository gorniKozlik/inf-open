#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    #ifdef LOCAL
    freopen("_test.in", "r", stdin);
    freopen("_test.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    while (q--) {
        int k;
        cin >> k;
        cout << k << ' ';
    }
}