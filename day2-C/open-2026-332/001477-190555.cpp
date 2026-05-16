#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

//#define int long long

const int INF= 1e9 + 7;
const int mod = 1e9 + 7;

const int maxn = 4e5 + 5;
int tree[maxn * 4];
int add[maxn * 4];

void push(int i, int l, int r) {
    if (r - l == 1 || add[i] == 0)return;
    tree[i * 2 + 1] += add[i];
    tree[i * 2 + 2] += add[i];
    add[i * 2 + 2] += add[i];
    add[i * 2 + 1] += add[i];
    add[i] = 0;
}

void updt(int i, int l, int r, int ql, int qr, int val) {
    if (ql <= l && qr >= r) {
        tree[i] += val;
        add[i] += val;
        return;
    }
    if (ql >= r || qr <= l) {
        return;
    }
    int m = (l + r) / 2;
    push(i, l, r);
    updt(i * 2 + 1, l, m, ql, qr, val);
    updt(i * 2 + 2, m, r, ql, qr, val);
    tree[i] = max(tree[i * 2 + 1], tree[i * 2 + 2]);
}

int get(int i, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return tree[i];
    }
    if (ql >= r || qr <= l) {
        return 0;
    }
    int m = (l + r) / 2;
    push(i, l, r);
    return max(get(i * 2 + 1, l, m, ql, qr), get(i * 2 + 2, m, r, ql, qr));
}

void solve() {
    int n,q; cin >> n >> q;
    vector<array<int, 3>> v(n);
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1];
        nums.push_back(v[i][0]);
        nums.push_back(v[i][1]);
        v[i][2] = i;
    }
    sort(all(nums));
    map<int, int> ma;
    int cnt = 1;
    for (auto i : nums) {
        if (ma[i] == 0)ma[i] = cnt++;
    }
    int n1 = 2 * n + 5;
    for (auto &[l, r,in] : v) {
        l= ma[l];
        r = ma[r];
        updt(0, 0, n1, l, r + 1, 1);
        // cout << l << ' ' << r << ' ' << 1 << '\n';
    }
    int nu = get(0, 0, n1, 0, n1);
    vector<int> kk(q);
    for (auto &i : kk)cin >> i;
    vector<int> ans(q);
    int ind = 0;
    int ad = 0;
    vector<array<int, 3>> v1;
    for (auto [l, r, in] : v) {
        v1.pb({l, r, in});
    }
    sort(all(v), [](array<int, 3> &a, array<int, 3>&b) {
        return a[1] < b[1];
    });

    sort(all(v1), [](array<int, 3> &a, array<int, 3>&b) {
        return a[0] < b[0];
    });


    vector<bool> used(n);
    int l1 = 0, r1 = n - 1;
    while (ind < q) {
        while (ind < q && nu >= kk[ind]) {
            ans[ind] = ad;
            ind++;
        }
        if (ind == q)break;
        ad++;

        while (l1 - 1 < n && used[v[l1][2]])l1++;
        while (r1 > 0  && used[v1[r1][2]])r1--;
        updt(0, 0, n1, v[l1][0], v[l1][1] + 1, -1);
        // cout << v[l1][0] << ' ' << v[l1][1] << ' ' << -1 << '\n';

        updt(0, 0, n1, v1[r1][0], v1[r1][1] + 1, -1);
        // cout << v1[r1][0] << ' ' << v1[r1][1] << ' ' << -1 << '\n';

        updt(0, 0, n1, v[l1][0], v1[r1][1] + 1, 1);
        // cout << v[l1][0] << ' ' << v1[r1][1] << ' ' << 1 << '\n';

        updt(0, 0, n1, v[l1][1], v1[r1][0] + 1, 1);
        // cout << v[l1][1] << ' ' << v1[r1][0] << ' ' << 1 << '\n';

        nu = get(0, 0, n1, 0, n1);
        used[v[l1][2]] = true;
        used[v1[r1][2]] = true;
        // cout << nu << '\n';
        // break;


    }

    for (auto i : ans)cout << i << ' ';




}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }
}
