#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using namespace std;

struct event {
    int x;
    int type;
};

const int logn = 20;

vector<int> powers;
vector<vector<int> > st(logn);

int get_max(int l, int r) {
    int len = r - l + 1;
    int pw = powers[len];
    return max(st[pw][l], st[pw][r - ((1 << (pw))) + 1]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    powers.resize(2 * n + 5);
    powers[0] = 0;
    powers[1] = 0;
    for (int i = 2; i < 2 * n + 5; ++i)
        powers[i] = powers[i - 1] + ((i & (i - 1)) == 0);

    vector<event> events;
    for (int i = 0; i < n; ++i) {
        int st, f;
        cin >> st >> f;
        events.push_back({st, 1});
        events.push_back({f, -1});
    }
    sort(events.begin(), events.end(), [](const event &a, const event &b) {
        if (a.x == b.x)
            return a.type < b.type;
        return a.x < b.x;
    });
    vector<int> ind;
    for (auto x: events)
        ind.push_back(x.x);

    int am = 0;
    vector<int> amount(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        if (events[i].type == 1) {
            am += events[i].type;
            amount[i] = am;
        } else {
            amount[i] = am;
            am += events[i].type;
        }
    }

    st[0] = amount;
    for (int i = 1; i < logn; ++i) {
        st[i].resize(2 * n);
        for (int j = 0; j < 2 * n; ++j)
            st[i][j] = max(st[i - 1][j], st[i - 1][min(2 * n - 1, j + (1 << (i - 1)))]);
    }

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        int mx = get_max(k, 2 * n - k - 1);
        if (events[k - 1].type == 1)
            mx = max(mx, amount[k - 1]);
        else
            mx = max(mx, amount[k - 1] - 1);

        if (events[2 * n - k].type == -1)
            mx = max(mx, amount[2 * n - k]);
        else
            mx = max(mx, amount[2 * n - k] - 1);

        if (mx >= k)
            cout << 0 << ' ';
        else
            cout << (k - mx + 1) / 2 << ' ';
    }
}
