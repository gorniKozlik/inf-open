#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <random>
#include <vector>
#include <random>
using namespace std;
using ll = long long;
using ld = long double;
using lll = __int128;
const ll maxn = 500'000;
mt19937 rnd(23);
struct ev {
    int x, type, ind;
};
bool cmp(ev a, ev b) {
    return a.x < b.x;
}
ev sp[maxn];
int tot = 0;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q; cin >> n >> q;

    for (int i = 0 ; i < n; ++i) {
        int l, r; cin >> l >> r;
        sp[tot++] = {l, 0, i};
        sp[tot++] = {r, 1, i};
    }
    sort(sp, sp + tot,cmp);
    vector<int> qq(q);
    for (int i = 0 ; i < q; ++i) {
        cin >> qq[i];
        if (qq[i] <= 1) {
            cout << 0 << ' ';
        } else {
            cout << qq[i] / 2 << ' ';
        }
        //cout << max(qq[i]-1, 0) << ' ';
    }
    return 0;
    int cnt = 0 ;
    for (int i = 0 ; i < n; ++i) {
        if (sp[i].type == 1) {
            cnt++;
        }
    }
    cout << cnt;
}