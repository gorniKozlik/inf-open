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
const ll maxn = 500'000, inf = 1'000'000'000'000;
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

    vector<ll> ans(n+10, inf);
    ll prev_cur = 0;
    ll next_cur = n;
    ll prev_ans = 0;
    ll next_ans = 0;
    ll cur = 0;
    ll mx = 0;
    for (int i= 0; i < n; ++i) {
        if (sp[i].type == 0) {
            next_cur -= 1;
            cur += 1;
            mx = max(mx, cur);
            ans[cur] = 0;
            ans[cur + min(prev_cur, next_cur) * 2] = min(prev_cur, next_cur);
        } else {
            cur -= 1;
            prev_cur += 1;
            ans[cur] = 0;
            ans[cur + min(prev_cur, next_cur) * 2] = min(prev_cur, next_cur);
        }
    }
    for (int i = 0 ; i <= mx; ++i) {
        ans[mx] = 0;
    }
    cur = 0;
    for (int i = mx + 1; i < ans.size(); ++i) {
        cur += 1;
        cur = min(cur, ans[i]);
        ans[i] = cur;
    }
    vector<int> qq(q);
    for (int i = 0 ; i < q; ++i) {
        int x; cin >> x;
        cout << ans[x] << ' ';

    }
}