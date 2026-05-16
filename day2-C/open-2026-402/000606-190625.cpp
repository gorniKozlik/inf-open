 // hello, it is a very good problem
#include <bits/stdc++.h>

using namespace std;
main() {
    int n, q;
    cin >> n >> q;
    vector<int> l(n), r(n);
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        ev.push_back({l[i], 1});
        ev.push_back({r[i], -1});
    }
    int cnto = 0, cntc = 0, cntu = n;
    set<pair<int, int>> s;
    sort(ev.begin(), ev.end());
    for (auto [u, t] : ev) {
        if (t == 1) {
            cntu--;
            s.insert({-cnto - 1, cnto + 1 + min(cntu, cntc) * 2});
            if (cntc > cntu) {
                s.insert({-cnto, cnto + 2 + min(cntu, cntc) * 2});
            }
            cnto++;
        } else {
            cnto--;
            s.insert({-cnto - 1, cnto + 1 + min(cntu, cntc) * 2});
            if (cntc < cntu) {
                s.insert({-cnto, cnto + 2 + min(cntu, cntc) * 2});
            }
            cntc++;
        }
    }
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; ++i) {
        while((*s.begin()).second < i) {
            s.erase(s.begin());
        }
        ans[i] = (*s.begin()).first + i;
    }
    while (q--) {
        int x;
        cin >> x;
        if (ans[x] <= 0) {
            cout << 0 << ' ';
            continue;
        }
        cout << (ans[x] + 1) / 2 << ' ';
    }
}
/*
---- ----- --    --
  /  |   |  \    /
 /   |   |   \  /
---- -----    \/
*/
