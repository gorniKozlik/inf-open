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

const int inf = 1e18 + 10;
const int Mx = 1e6 + 10;
Event Evs[Mx];
int Qs[Mx];
int Best[Mx];
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
        Event e = Evs[i];
        cnt += e.type;
        int cntL = i + 1, cntR = 2 * N - i - 1;
        //cout << e.x << ": " << cntL << ' ' << cntR << ' ' << cnt << endl;
        Best[min(cntL, cntR)] = min(Best[min(cntL, cntR)], min(cntL, cntR) - cnt);
    }
    for (int i = N; i >= 1; i--) {
        Best[i] = min(Best[i], Best[i+1]);
    }
    for (int i = 0; i < Q; i++) {
        cout << Best[Qs[i]] / 2 << ' ';
    }
}
