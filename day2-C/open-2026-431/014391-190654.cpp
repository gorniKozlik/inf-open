#include <bits/stdc++.h>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz size
#define pb push_back
#define int long long

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int A = 5e5 + 5;

struct Node {
    int l, r, num;
};

ll n, q, i, a[A], t[A * 4], lazy[A * 4], cnt = 1, ans[A];
Node l[A], l1[A];
map<int, int> mp;

bool comp(Node a, Node b) {
    if (a.l != b.l) return a.l < b.l;
    else a.r < b.r;
}

void push(int v) {
    t[v] += lazy[v];
    lazy[v * 2] += lazy[v];
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
}

void upd(int v, int l, int r, int tl, int tr, int k) {
    push(v);
    push(v * 2);
    push(v * 2 + 1);
    if (tr < l || r < tl) return;
    if (l == tl && tr == r) {
        lazy[v] += k;
        push(v);
        return;
    }
    int mid = (l + r) / 2;
    upd(v * 2, l, mid, tl, min(mid, tr), k);
    upd(v * 2 + 1, mid + 1, r, max(tl, mid + 1), tr, k);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}

int32_t main() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL

    cin >> n >> q;
    for (i = 1; i <= n; i++) {
        cin >> l[i].l >> l[i].r;
        mp[l[i].l] = 1;
        mp[l[i].r] = 1;
    }
    for (auto &to : mp) to.se = cnt++;
    for (i = 1; i <= n; i++) {
        l[i].l = mp[l[i].l];
        l[i].r = mp[l[i].r];
        upd(1, 1, n, l[i].l, l[i].r, 1);
        l1[i] = l[i];
        ans[i] = 1e9;
//        cout << l[i].l << " " << l[i].r << endl;
    }
//    cout << endl;

    int y = n;
    ans[t[1]] = 0;
    cnt = 1;
    y = n;
    int tt = 10;
    while (tt--) {
        y = n;
        sort(l + 1, l + n + 1, comp);
        for (i = 1; i <= n; i++) {
            if (i >= y) break;
            if (l[i].l <= l[y].l && l[y].r <= l[i].r) continue;
            upd(1, 1, n, l[i].l, l[i].r, -1);
            upd(1, 1, n, l[y].l, l[y].r, -1);
            vector<int> dm = {l[i].l, l[i].r, l[y].l, l[y].r};
            sort(all(dm));
    //        cout << dm[0] << " " << dm[3] << " " << dm[1] << " " << dm[2] << endl;
            upd(1, 1, n, dm[0], dm[3], 1);
            upd(1, 1, n, dm[1], dm[2], 1);
            l[i] = {dm[0], dm[3]};
            l[y] = {dm[1], dm[2]};
            ans[t[1]] = min(ans[t[1]], cnt);
            cnt++;
            y--;
        }
    }
    for (i = n - 1; i >= 1; i--) ans[i] = min(ans[i + 1], ans[i]);
    int x;
    while (q--) {
        cin >> x;
        if (ans[x] >= 1e9) {
            exit(1);
        }
        cout << ans[x] << " ";
    }
}
