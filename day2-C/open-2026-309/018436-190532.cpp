#include <iostream>

using namespace std;

int main() {
    int n, q, k, a, b;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
    }
    for (int i = 0; i < q; ++i) {
        cin >> k;
        cout << k - 1 << " ";
    }
    return 0;
}
