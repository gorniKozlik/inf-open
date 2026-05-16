#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <random>
using namespace std;

#define int long long

struct Segm {
    int l, r;
};

const int Mx = 1e6 + 10;
Segm A[Mx];
int N, Q;

signed main() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> A[i].l >> A[i].r;
    }
    for (int i = 0; i < Q; i++) {
        int k;
        cin >> k;
        if (k == 1) {
            cout << 0;
            continue;
        }
        cout << (k + k % 2) / 2 << '\n';
    }
}
