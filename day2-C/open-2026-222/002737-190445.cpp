#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> evs;
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        evs.push_back({l, 1});
        evs.push_back({r, -1});
    }
    sort(evs.begin(), evs.end());
    string psp;
    for(auto [x, t] : evs) {
        if(t == 1) psp.push_back('(');
        else psp.push_back(')');
    }
    int cur = 0;
    vector<int> anss(n + 1);
    int ops = 0;
    while(true) {
        int bal = 0, mxbal = 0;
        for(char c : psp) {
            if(c == '(') {
                bal++;
                mxbal = max(mxbal, bal);
            } else {
                bal--;
            }
        }
        assert(bal == 0);
        while(cur < mxbal) anss[cur++] = ops;
        int aa = psp.find(')');
        int bb = psp.rfind('(');
        if(aa > bb) break;
        swap(psp[aa], psp[bb]);
        ops++;
    }
    while(q--) {
        int xx;
        cin >> xx;
        cout << anss[xx - 1] << ' ';
    }
    cout << '\n';
}
