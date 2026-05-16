#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

const int INF = 1e9 + 7;
const ll LL_INF = 4e18;

struct Query {
    int k;
    int ind;
};

const int LEFT = 1, RIGHT = -1;

struct Point {
    int x;
    int type;
};

vector<Point> arr;
vector<Query> qs;

int max_cover() {
    int ans = 0;
    int cur = 0;
    for (const auto& [x, type] : arr) {
        cur += type;
        ans = max(ans, cur);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, nQ;
    cin >> n >> nQ;


    int lb, rb;
    for (int i = 0; i < n; ++i) {
        cin >> lb >> rb;
        arr.push_back(Point{lb, LEFT});
        arr.push_back(Point{rb, RIGHT});
    }

    for (int q = 0; q < nQ; ++q) {
        int k;
        cin >> k;
        qs.push_back(Query{k, q});
    }

    sort(qs.begin(), qs.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.k < rhs.k;
    });

    sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {
       if (lhs.x != rhs.x) return lhs.x < rhs.x;
        return lhs.type > rhs.type;
    });

    vector<int> ans(nQ, INF);
    int cur_ops = 0;
    assert(arr.size() == 2 * n);

    while (true) {
        int mx_c = max_cover();

        //cout << "AFTER " << cur_ops << ' ' << mx_c << '\n';
        for (int q = 0; q < nQ; ++q) {
            if (qs[q].k <= mx_c) ans[qs[q].ind] = min(ans[qs[q].ind], cur_ops);
        }

        int lmr = INF, rml = -INF;
        int lmr_i = -1, rml_i = -1;

        for (int i = 0; i < 2 * n; ++i) {
            if (arr[i].type == LEFT && arr[i].x > rml) {
                rml = arr[i].x;
                rml_i = i;
            }
            if (arr[i].type == RIGHT && arr[i].x < lmr) {
                lmr = arr[i].x;
                lmr_i = i;
            }
        }

        if (rml <= lmr) break;

        swap(arr[lmr_i].type, arr[rml_i].type);
        cur_ops++;
    }

    for (int i = 0; i < nQ; ++i) cout << ans[i] << ' ';

    return 0;
}