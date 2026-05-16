#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

struct query {
    int x, nmb, c;
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector <query> v;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        v.push_back(query{l, i, 0});
        v.push_back(query{r, i, 1});
    }

    sort(v.begin(), v.end(),
        [&](query a, query b) {
            return a.x < b.x || (a.x == b.x && a.c < b.c);
        }
    );

    int k = 0;
    int x1 = 0;
    int x2;


    vector <pair <int, int>> w;
    for (int i = 0; i < 2 * n; ++i) {
        if (v[i].c == 0) {
            k++;
        }
        if (v[i].c == 1) {
            k--;
            x1++;
        }
        x2 = n - k - x1;
        w.emplace_back(k, min(x1, x2));
    }

    for (int i = 0; i < q; ++i) {
        int ans = n;
        cin >> k;
        for (int i = 0; i < w.size(); ++i) {
            if (w[i].first >= k) ans = 0;
            else if (w[i].first + 2 * w[i].second >= k) ans = min(ans, (k - w[i].first + 1) / 2);
            else ans = min(ans, k - w[i].first - w[i].second);
        }
        cout << ans << " ";
    }
    return 0;
}
