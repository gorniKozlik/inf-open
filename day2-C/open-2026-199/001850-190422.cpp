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

    vector <int> ans(n + 1, n);

    int mx = 0;
    for (auto[k, x] : w) {
        mx = max(mx, k);
    }

    for (int i = 0; i <= mx; ++i) {
        ans[i] = 0;
    }

    set <pair <int, int>> s1;
    set <int> s2;
    vector <query> t;

    for (int i = 0; i < w.size(); ++i) {
        t.push_back(query{w[i].first + 2 * w[i].second, i, w[i].second});
        s1.insert({-w[i].first, i});
    }
    sort(t.begin(), t.end(),
        [&](query a, query b) {
            return a.x > b.x;
        }
    );

    for (int i = mx + 1; i <= n; ++i) {
        while (!t.empty() && t.back().x < i) {
            s2.insert(- t.back().x + t.back().c);
            s1.erase({- t.back().x + 2 * t.back().c, t.back().nmb});
            t.pop_back();
        }
        if (!s1.empty()) {
            int k = (*s1.begin()).first;
            ans[i] = min(ans[i], (i + k + 1) / 2);
        }
        if (!s2.empty()) {
            int k = *s2.begin();
            ans[i] = min(ans[i], i + k);
        }
    }

    for (int i = 0; i < q; ++i) {
        cin >> k;
//        for (int i = 0; i < w.size(); ++i) {
//            if (w[i].first >= k) ans = 0;
//            else if (w[i].first + 2 * w[i].second >= k) ans = min(ans, (k - w[i].first + 1) / 2);
//            else ans = min(ans, k - w[i].first - w[i].second);
//        }
        cout << ans[k] << " ";
    }
    return 0;
}
