#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int long long
#define pii pair<int, int>
#define F first
#define S second


const int inf = 1e9;

int maxn = 0;

vector<pii> tr;

void push(int ind) {
    if (2 * ind + 1 < tr.size()) {
        tr[2 * ind].F += tr[ind].S;
        tr[2 * ind].S += tr[ind].S;
        tr[2 * ind + 1].F += tr[ind].S;
        tr[2 * ind + 1].S += tr[ind].S;
    }
    tr[ind].S = 0;
}

int get(int ind, int l, int r, int lq, int rq) {
    push(ind);
    if (lq <= l && r <= rq) {
        return tr[ind].F;
    }
    if (lq >= r || rq <= l) {
        return 0;
    }
    int mid = (l + r) / 2;
    return max(get(2 * ind, l, mid, lq, rq), get(2 * ind + 1, mid, r, lq, rq));
}

void upd(int ind, int l, int r, int lq, int rq, int x) {
    push(ind);
    if (lq <= l && r <= rq) {
        tr[ind].S += x;
        tr[ind].F += x;
        return;
    }
    if (lq >= r || rq <= l) {
        return;
    }
    int mid = (l + r) / 2;
    upd(2 * ind, l, mid, lq, rq, x);
    upd(2 * ind + 1, mid, r, lq, rq, x);
    tr[ind].F = max(tr[2 * ind].F, tr[2 * ind + 1].F);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> x;
    vector<pii> otr(n);
    for (int i = 0; i < n; i++) {
        cin >> otr[i].F >> otr[i].S;
        x.push_back(otr[i].F);
        x.push_back(otr[i].S);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    for (auto &i : otr) {
        i.F = lower_bound(x.begin(), x.end(), i.F) - x.begin();
        i.S = lower_bound(x.begin(), x.end(), i.S) - x.begin();
    }
    maxn = 10 * n;
    int N = 2 * n + 1;
    //maxn = 6e6;
    tr.resize(maxn);
    set<pii> l, r;
    for (int i = 0; i < n; i++) {
        upd(1, 0, N, otr[i].F, otr[i].S, 1);
        l.insert({-otr[i].F, i});
        r.insert({otr[i].S, i});
    }
    vector<int> ans(n);
    int y = 0;
    /*for (int j = 0; j < N; j++) {
        cout << get(1, 0, N, j, j + 1) << " ";
    }
    cout << endl;*/
    for (int i = 0; i < n; i++) {
        if (tr[1].F >= i + 1) {
            ans[i] = y;
            continue;
        }
        y++;
        pii a1 = *l.begin(), a2 = *r.begin();
        l.erase(a1);
        r.erase(a2);
        a1.F *= -1;
        otr[a2.S] = {otr[a2.S].F, a1.F};
        otr[a1.S] = {a2.F, otr[a1.S].S};
        r.insert({a1.F, a2.S});
        l.insert({-a2.F, a1.S});
        upd(1, 0, N, a2.F, a1.F, 2);
        /*cout << a2.F << " " << a1.F << endl;
        for (int j = 0; j < N; j++) {
            cout << get(1, 0, N, j, j + 1) << " ";
        }
        cout << endl;*/
        ans[i] = y;
    }
    for (int i = 0; i < q; i++) {
        int f;
        cin >> f;
        cout << ans[f - 1] << " ";
    }
    return 0;
} 