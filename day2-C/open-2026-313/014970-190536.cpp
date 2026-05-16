#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <numbers>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <bit>
using namespace std;
using ll = long long;
using db = double;


int main() {
    ll n, q, t, i, k;
    cin >> n >> q;
    vector<pair<ll, ll>> cuts(n);
    for (int i = 0; i < n; i++) {
        cin >> cuts[i].first >> cuts[i].second;
    }

    for (int i = 0; i < q; i++) {
        cin >> k;
        cout << k;
    }
}
