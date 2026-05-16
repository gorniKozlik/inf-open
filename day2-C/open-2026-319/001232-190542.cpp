#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>
#include <stack>
#include <deque>
#include <queue>
#include <climits>
#include <cmath>
#include <bitset>
#include <string>
#include <utility>
#include <cstring>
#include <iomanip>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define mid (l + r) / 2
//#define int long long

constexpr int maxn = 200'002;
int l[maxn];
int r[maxn];
int k[maxn];
struct Event {
    int pos;
    bool type;
};
bool operator<(Event a, Event b) {
    if (a.pos == b.pos) return a.type > b.type;
    return a.pos < b.pos;
}
vector<Event> e;
int pers() {
    int cnt = 0;
    int mx = 0;
    for (Event i : e) {
        if (i.type == true) {
            cnt++;
        } else {
            cnt--;
        }
        mx = max(mx, cnt);
    }
    return mx;
}
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int li, ri; cin >> li >> ri;
        l[i] = li;
        r[i] = ri;
        e.push_back({li, true});
        e.push_back({ri, false});
    }
    sort(all(e));
    vector<Event> e0 = e;
    int nw = pers();
    for (int iq = 0; iq < q; iq++) {
        int ki; cin >> ki;
        int opers = 0;
        int nw0 = nw;
        while (nw0 < ki) {
        int leastr = INT_MAX;
        int rind = 0;
        int mostl = INT_MIN;
        int lind = 0;
        for (int i = 0; i < e.size(); i++) {
            if (e[i].type == true) {
                mostl = e[i].pos;
                lind = i;
            } else if (leastr == INT_MAX) {
                leastr = e[i].pos;
                rind = i;
            }
        }
        e[lind].type = false;
        e[rind].type = true;
        opers++;
        nw0 = pers();
        }
        cout << opers << ' ';
        e = e0;
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
