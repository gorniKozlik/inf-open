#include<bits/stdc++.h>
using namespace std;
main() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    int l[n + 1], r[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    while (q--) {
        int k;
        cin >> k;
        cout << (k) / 2 << endl;
    }
}