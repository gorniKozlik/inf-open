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

struct Event {
    int x, type, id;
};

const int q = 0;
const int inf = 1e18 + 10;
const int Mx = 1e6 + 10;
Event Evs[Mx];
int Qs[Mx];
int Best[Mx];
int Upd[Mx][2];
int N, Q;


bool cmp (Event e1, Event e2) {
    if (e1.x != e2.x) {
        return e1.x < e2.x;
    }
    if (e1.type != e2.type) {
        return e1.type > e2.type;
    }
    return e1.id < e2.id;
}

void push(int v) {
    Upd[v*2][0] = max(Upd[v*2][0], Upd[v][0]);
    Upd[v*2 + 1][0] = max(Upd[v*2 + 1][0], Upd[v][0]);
    Upd[v*2][1] = max(Upd[v*2][1], Upd[v][1]);
    Upd[v*2 + 1][1] = max(Upd[v*2 + 1][1], Upd[v][1]);
}

void upd(int v, int l, int r, int ql, int qr, int cnt, bool par) {
    if (l > qr || r < ql) {
        return;
    }
    if (l >= ql && r <= qr) {
        //cout << v << ' ' << par << endl;
        Upd[v][par] = max(Upd[v][par], cnt);
        return;
    }
    int m = (l + r) / 2;
    push(v);
    upd(v*2, l, m, ql, qr, cnt, par);
    upd(v*2 + 1, m + 1, r, ql, qr, cnt, par);
}

int find_x(int v, int l, int r, int id, bool par) {
    if (l > id || r < id) {
        return 0;
    }
    if (l == id && id == r) {
        return Upd[v][par];
    }
    int m = (l + r) / 2;
    push(v);
    int x1 = find_x(v*2, l, m, id, par);
    int x2 = find_x(v*2 + 1, m + 1, r, id, par);
    return x1 + x2;
}

signed main() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int l, r;
        cin >> l >> r;
        Evs[2*i] = {l, 1, 2*i};
        Evs[2*i+1] = {r, -1, 2*i+1};
    }
    for (int i = 0; i < Q; i++) {
        cin >> Qs[i];
    }
    sort(Evs, Evs + 2 * N, cmp);
    int cnt = 0;
    fill(Best, Best + N + 10, inf);
    for (int i = 0; i < 2 * N; i++) {
        //cout << "i: " << i << endl;
        Event e = Evs[i];
        cnt += e.type;
        int cntL = i + 1, cntR = 2 * N - i - 1;
        upd(1, 1, N, cnt % 2, min(cntL, cntR), cnt, cnt % 2);
        //Best[min(cntL, cntR)] = min(Best[min(cntL, cntR)], min(cntL, cntR) - cnt);
    }
    //for (int i = N; i >= 1; i--) {
        //Best[i] = min(Best[i], Best[i+1]);
        //cout << Best[i] << endl;
    //}
    //cout << "test: " << Best[Qs[3]] << endl;
    for (int i = 0; i < Q; i++) {
        if (Best[Qs[i]] % 2) {
            return 1;
        }
        cout << max(q, Qs[i] - find_x(1, 1, N, Qs[i], Qs[i] % 2)) / 2 << ' ';
    }
}
