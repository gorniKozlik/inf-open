#include <bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(), v.end()

const int INF = -1e9;

struct MO { int h, r; };
struct ME { int s, c; };

bool operator<(ME a, ME b) {
    if (a.c == b.c) return a.s > b.s;
    return a.c < b.c;
}

int main() {
    int n, m, k, x; cin >> n >> m >> k >> x;
    vector<MO> mo(n); for (MO &moi: mo) cin >> moi.h >> moi.r;
    vector<ME> me(m); for (ME &mei: me) cin >> mei.s >> mei.c;

    vector<int> co(n+1);
    for (int i = 0; i < n; i++) co[i+1] = co[i] + mo[i].r;

    sort(ALL(me));

    vector<ME> me0 = { me[0] };
    for (ME mei: me) if (mei.s > me0.back().s) me0.push_back(mei);
    
    swap(me0, me);
    m = me.size();

    vector<int> s(m);
    for (int i = 0; i < m; i++) s[i] = me[i].s;

    vector<int> ms(n);
    for (int i = 0; i < n; i++) ms[i] = lower_bound(ALL(s), mo[i].h) - s.begin();
    if (*max_element(ALL(ms)) >= m) {
        cout << "No\n";
        return 0;
    }

    vector<int> mr;

    multiset<int> q;
    for (int i = 0; i < k; i++) {
        q.insert(ms[i]);
        if (i != k-1) mr.push_back(*q.rbegin());
    }
    
    mr.push_back(*q.rbegin());
    for (int i = 0; i < n-k; i++) {
        q.erase(q.find(ms[i]));
        q.insert(ms[k+i]);
        mr.push_back(*q.rbegin());
    }

    for (int i = 0; i < k-1; i++) {
        q.erase(q.find(ms[n-k+i-1]));
        mr.push_back(*q.rbegin());
    }

    vector<int> dp(mr.size() + 2);
    dp[0] = x;

    multiset<pair<int, int>> w = { };
    
    for (int i = 1; i < k; i++) {
        dp[i] = dp[0] - me[mr[i-1]].c;
        if (dp[i] < 0) dp[i] = INF;
        w.insert({dp[i], -k+i});
    }

    for (int i = 0; i < n; i++) {
        int s = max(0, w.rbegin()->second);
        int e = i+1;
        dp[k+i] += co[e] - co[s];
        dp[k+i] += w.rbegin()->first - me[mr[k+i-1]].c;
        if (dp[k+i] < 0) dp[k+i] = INF;
        w.erase(w.find({dp[i+1], i-k+1}));
        w.insert({dp[k+i], i});
    }

    cout << (w.rbegin()->first >= 0 ? "Yes" : "No");
}