#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Node {
    ll a, max_tree;
};

vector<Node> tree;
vector<pair<ll, ll>> points;

bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
    return a.second < b.second;
}

void build(ll m, ll l, ll r, ll now) {
    if (r - l == 1) {
        tree[m].a = points[l].second;
        tree[m].max_tree = now + tree[m].a;
        return;
    }

    build(m * 2 + 1, l, (l + r) / 2, now);
    build(m * 2 + 2, (l + r) / 2, r, now + tree[m * 2 + 1].a);

    tree[m].a = tree[m * 2 + 1].a + tree[m * 2 + 2].a;
    tree[m].max_tree = now + tree[m].a;
    tree[m].max_tree = max(tree[m].max_tree, max(tree[m * 2 + 1].max_tree, tree[m * 2 + 2].max_tree));
}

void update(ll m, ll l, ll r, ll now, ll x) {
    if (r <= x || x < l) {
        return;
    }
    if (r - l == 1) {
        tree[m].a *= -1;
        tree[m].max_tree = now + tree[m].a;
        return;
    }

    update(m * 2 + 1, l, (l + r) / 2, now, x);
    update(m * 2 + 2, (l + r) / 2, r, now + tree[m * 2 + 1].a, x);

    tree[m].a = tree[m * 2 + 1].a + tree[m * 2 + 2].a;
    tree[m].max_tree = now + tree[m].a;
    tree[m].max_tree = max(tree[m].max_tree, max(tree[m * 2 + 1].max_tree, tree[m * 2 + 2].max_tree));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;

    points.resize(n * 2);
    vector<pair<ll, ll>> a(n);

    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;

        points[i * 2] = {a[i].first, 1};
        points[i * 2 + 1] = {a[i].second, -1};
    }

    sort(points.begin(), points.end());
    ll mid = points[n].first;
    map<ll, ll> inds;
    for (ll i = 0; i < n * 2; ++i)
        inds[points[i].first] = i;

    tree.resize(n * 8);
    build(0, 0, n * 2, 0);

    vector<ll> ans(n);
    ll last_ans = tree[0].max_tree;

    sort(a.begin(), a.end(), cmp);

    ll l = 0, r = n - 1, k = 1;
    while (l < r) {
        while (l < r && a[r].first < mid) {
            r--;
        }
        if (l < r) {
            update(0, 0, n * 2, 0, inds[a[l].second]);
            update(0, 0, n * 2, 0, inds[a[r].first]);
            while (last_ans < tree[0].max_tree) {
                ans[last_ans++] = k;
            }
            k++;
            l++;
            r--;
        }
    }

    while (q--) {
        ll k;
        cin >> k;

        cout << ans[--k] << " ";
    }
}