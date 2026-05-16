#include <iostream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <random>
#include <numeric>


using namespace std;
using ll = long long;
using ld = long double;
using ui = unsigned int;
using ull = unsigned long long;

struct Seg {
    int l, r;
};

struct Query {
    int k, i;
    
    bool operator<(const Query &a) const {
        if (k != a.k) return k < a.k;
        return i < a.i;
    }
};

istream& operator>>(istream& is, Seg &a) {
    is >> a.l >> a.r;
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<Seg> segs(n);
    for (auto &i : segs) cin >> i;
    vector<Query> req(q);
    for (int i = 0; i < q; ++i) {
        cin >> req[i].k;
        req[i].i = i;
    }
    sort(req.begin(), req.end());
    vector<int> ans(q);
    for (auto [k, i] : req) {
        ans[i] = k / 2;
    }
    for (auto i : ans) cout << i << ' ';
}