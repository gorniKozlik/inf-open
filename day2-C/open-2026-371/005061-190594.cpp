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
    while (q--) {
        int k;
        cin >> k;
        int ans = INF;
        for (auto pt : pts) {
            int cntLeft = 0, cntRight = 0, cntGood = 0;
            int l = 0, r = n + 1;
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (subsSortR[m - 1].second < pt.first) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cntLeft = l;
            l = 0, r = n + 1;
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (subsSortL[m - 1].first > pt.first) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cntRight = l;
            cntGood = n - cntLeft - cntRight;
            if (cntGood >= k) {
                ans = 0;
                break;
            } else {
                int maxK = cntGood + (min(cntLeft, cntRight) * 2);
                if (cntLeft != cntRight) {
                    if (cntLeft > cntRight) {
                        if (pt.second == 0) {
                            ++maxK;
                        }
                    } else {
                        if (pt.second == 1) {
                            ++maxK;
                        }
                    }
                }
                if (maxK < k) {
                    continue;
                }
                int cntNeed = k - cntGood;
                int newAns = (cntNeed / 2) + (cntNeed % 2);
                ans = min(ans, newAns);
            }
        }
        cout << ans << ' ';
    }
}