#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <numeric>
#include <iomanip>
#include <random>
#include <queue>
#include <stack>
#include <deque>
#include <ranges>
#include <chrono>
#define eb emplace_back

using namespace std;

using ll = long long;
using lll = __int128;
using db = double;
using ld = long double;

const int INF = 1'000'000'000;
const ll LINF = 1'000'000'000'000'000'000;
const ll MOD = 998'244'353;

struct Point {
    ld x, y;

    Point(): x(0), y(0) {}

    Point(ld x, ld y): x(x), y(y) {}

    Point(Point from, Point to): x(to.x - from.x), y(to.y - from.y) {}

    ld operator* (Point other) {
        ld ans = (x * other.x) + (y * other.y);
        return ans;
    }

    ld operator% (Point other) {
        ld ans = (x * other.y) - (y * other.x);
        return ans;
    }

    Point operator* (ld val) {
        Point ans(x * val, y * val);
        return ans;
    }

    ld len() {
        ld ans = sqrtl((x * x) + (y * y));
        return ans;
    }

    Point norm() {
        Point ans = *this;
        ans.x /= this->len();
        ans.y /= this->len();
        return ans;
    }
};

bool compL(pair <int, int> a, pair <int, int> b) {
    return (a.first < b.first);
}

bool compR(pair <int, int> a, pair <int, int> b) {
    return (a.second < b.second);
}

struct ForPoint {
    int cntLeft, cntRight, cntGood, type;

    ForPoint(): cntLeft(0), cntRight(0), cntGood(0), type(0) {}
};

vector <int> tree;

void push(int v) {
    int lft = (v * 2) + 1, rgt = lft + 1;
    if (tree[v] == -1) {
        return;
    }
    tree[lft] = tree[v];
    tree[rgt] = tree[v];
    tree[v] = -1;
}

void update(int v, int l, int r, int ql, int qr, int val) {
    if ((r <= ql) || (l >= qr)) {
        return;
    }
    if ((l >= ql) && (r <= qr)) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2, lft = (v * 2) + 1, rgt = lft + 1;
    push(v);
    update(lft, l, m, ql, qr, val); update(rgt, m, r, ql, qr, val);
}

int get(int v, int l, int r, int idx) {
    if (r - l == 1) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2, lft = (v * 2) + 1, rgt = lft + 1;
    if (idx < m) {
        return get(lft, l, m, idx);
    }
    return get(rgt, m, r, idx);
}

bool compPts(ForPoint a, ForPoint b) {
    return (a.cntGood < b.cntGood);
}

int main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> pts;
    vector <pair <int, int>> subs(n);
    for (int i = 0; i < n; ++i) {
        cin >> subs[i].first >> subs[i].second;
        pts.eb(subs[i].first, 0);
        pts.eb(subs[i].second, 1);
    }
    sort(pts.begin(), pts.end());
    vector <pair <int, int>> subsSortL = subs, subsSortR = subs;
    sort(subsSortL.rbegin(), subsSortL.rend(), compL);
    sort(subsSortR.begin(), subsSortR.end(), compR);
    vector <ForPoint> calced(pts.size());
    for (int i = 0; i < pts.size(); ++i) {
        int l = 0, r = n + 1;
        calced[i].type = pts[i].second;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (subsSortR[m - 1].second < pts[i].first) {
                l = m;
            } else {
                r = m;
            }
        }
        calced[i].cntLeft = l;
        l = 0, r = n + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (subsSortL[m - 1].first > pts[i].first) {
                l = m;
            } else {
                r = m;
            }
        }
        calced[i].cntRight = l;
        calced[i].cntGood = n - calced[i].cntLeft - calced[i].cntRight;
    }
    sort(calced.begin(), calced.end(), compPts);
    tree.resize((n + 1) * 4, -1);
    for (int i = 0; i < calced.size(); ++i) {
        int maxK = calced[i].cntGood + (min(calced[i].cntLeft, calced[i].cntRight) * 2);
        if (calced[i].cntLeft != calced[i].cntRight) {
            if ((calced[i].cntLeft > calced[i].cntRight) && (calced[i].type == 0)) {
                ++maxK;
            }
            if ((calced[i].cntRight > calced[i].cntLeft) && (calced[i].type == 1)) {
                ++maxK;
            }
        }
        update(0, 0, n + 1, 1, maxK + 1, i);
    }
    while (q--) {
        int k;
        cin >> k;
        int idx = get(0, 0, n + 1, k);
        if (calced[idx].cntGood >= k) {
            cout << "0 ";
            continue;
        }
        int needCnt = k - calced[idx].cntGood;
        int ans = (needCnt / 2) + (needCnt % 2);
        cout << ans << ' ';
    }
}