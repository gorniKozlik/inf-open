#include <bits/stdc++.h>

#pragma GCC optimize("Ofast", "O3", "unroll-loops")
#pragma GCC target("avx2", "bmi", "bmi2", "lzcnt", "popcnt")

using namespace std;
const int MAXN = 2e5 + 1;
const int INF = 1e9 + 7;

int sz;
vector<pair<int, int>> t;

vector<int> l, r;
vector<char> used;
vector<int> ans;

void push(int v) {
    t[v].first += t[v].second;

    if (v * 2 + 2 < 4 * sz) {
        t[v * 2 + 1].second += t[v].second;
        t[v * 2 + 2].second += t[v].second;
    }
    t[v].second = 0;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        t[v].second += x;
        push(v);
        return;
    }
    if (l >= qr || r <= ql) {
        return;
    }
    int mid = (l + r) / 2;
    push(v);
    update(v * 2 + 1, l, mid, ql, qr, x);
    update(v * 2 + 2, mid, r, ql, qr, x);
    push(v * 2 + 1);
    push(v * 2 + 2);
    t[v].first = max(t[v * 2 + 1].first, t[v * 2 + 2].first);
}

void rebuild(int v, int l, int r) {
    if (r - l == 1) {
        t[v].first = 0;
        t[v].second = 0;
        return;
    }
    int mid = (l + r) / 2;
    rebuild(v * 2 + 1, l, mid);
    rebuild(v * 2 + 2, mid, r);
}

bool comp1(int a, int b) {
    return (l[a] > l[b] || (l[a] == l[b] && r[a] > r[b]));
}
bool comp2(int a, int b) {
    return (r[a] < r[b] || (r[a] == r[b] && l[a] < l[b]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    l.resize(n);
    r.resize(n);
    ans.resize(n + 1, INF);
    used.resize(n + 1);
    vector<int> nums(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        nums[i * 2] = (l[i]);
        nums[i * 2 + 1] = (r[i]);
    }
    vector<int> k(q);
    for (auto &i : k)
        cin >> i;
    sort(nums.begin(), nums.end());
    int it = unique(nums.begin(), nums.end()) - nums.begin();
    nums.resize(it);
    int curpos = 0;
    unordered_map<int, int> pos;
    for (auto i : nums) {
        pos[i] = curpos++;
    }
    sz = curpos + 1;

    t.resize(4 * sz);
    for (int i = 0; i < n; ++i) {
        update(0, 0, sz, pos[l[i]], pos[r[i]] + 1, 1);
    }
    int curb = t[0].first;
    for (int i = 0; i <= curb; ++i) {
        ans[i] = 0;
    }

    vector<int> v1(n), v2(n);
    iota(v1.begin(), v1.end(), 0);
    iota(v2.begin(), v2.end(), 0);
    sort(v1.begin(), v1.end(), comp1);
    sort(v2.begin(), v2.end(), comp2);

    int i1 = n - 1, i2 = n - 1;
    int cnt = 1, cnt4n = 0;
    while (curb != n) {
        char f = 0;
        while (used[v1[i1]]) {
            i1--;
            if (i1 == -1) {
                f = 1;
                break;
            }
        }
        while (used[v2[i2]]){
            i2--;
            if (i2 == -1) {
                f = 1;
                break;
            }
        }
        if (f)
            break;
        int left = v1[i1], right = v2[i2];
        used[v1[i1]] = 1;
        used[v2[i2]] = 1;
        if (left == right) {
            continue;
        }
        update(0, 0, sz, pos[l[left]], pos[r[left]] + 1, -1);
        update(0, 0, sz, pos[l[right]], pos[r[right]] + 1, -1);
        int ll = pos[l[left]], lr = pos[r[left]],
            rl = pos[l[right]], rr = pos[r[right]];
        if (rr < ll)
            swap(ll, rr);
        if (rl < lr)
            swap(lr, rl);
        update(0, 0, sz, ll, rr + 1, 1);
        update(0, 0, sz, lr, rl + 1, 1);
        for (int i = curb + 1; i <= t[0].first; ++i) {
            ans[i] = min(ans[i], cnt);
        }
        cnt++;
        if (t[0].first != curb)
            cnt4n++;
        curb = t[0].first;
    }
    ans[n] = cnt4n;

    /*
    //rebuild(0, 0, sz);
    for (auto &i : t) {
        i.first = 0;
        i.second = 0;
    }
    for (int i = 0; i < n; ++i) {
        update(0, 0, sz, pos[l[i]], pos[r[i]] + 1, 1);
    }
    for (auto &i : used)
        i = 0;

    cnt = 1;
    curb = t[0].first;
    i1 = 0, i2 = 0;
    while (curb != n) {
        char f = 0;
        while (used[v1[i1]]) {
            i1++;
            if (i1 == n) {
                f = 1;
                break;
            }
        }
        while (used[v2[i2]]){
            i2++;
            if (i2 == n) {
                f = 1;
                break;
            }
        }
        if (f)
            break;
        int left = v1[i1], right = v2[i2];
        used[v1[i1]] = 1;
        used[v2[i2]] = 1;
        if (left == right) {
            continue;
        }
        update(0, 0, sz, pos[l[left]], pos[r[left]] + 1, -1);
        update(0, 0, sz, pos[l[right]], pos[r[right]] + 1, -1);
        int ll = pos[l[left]], lr = pos[r[left]],
            rl = pos[l[right]], rr = pos[r[right]];
        if (rr < ll)
            swap(ll, rr);
        if (rl < lr)
            swap(lr, rl);
        update(0, 0, sz, ll, rr + 1, 1);
        update(0, 0, sz, lr, rl + 1, 1);
        for (int i = curb + 1; i <= t[0].first; ++i) {
            ans[i] = min(ans[i], cnt);
        }
        cnt++;
        curb = t[0].first;
    }
    */


    for (auto &i : k) {
        cout << ans[i] << " ";
    }
}

/*

*/

