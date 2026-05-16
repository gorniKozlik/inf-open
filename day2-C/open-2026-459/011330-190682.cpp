#include <bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 1;
const int INF = 1e9 + 7;

int sz;
pair<int, int> t[4 * MAXN * 2];

char used[MAXN];
int ans[MAXN];

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

struct s {
    int l, r, idx;
};

bool comp1(s a, s b) {
    return (a.l > b.l || (a.l == b.l && a.r > b.r));
}
bool comp2(s a, s b) {
    return (a.r < b.r || (a.r == b.r && a.l < b.l));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < MAXN; ++i)
        ans[i] = INF;

    int n, q;
    cin >> n >> q;

    vector<s> v(n);

    vector<int> nums(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].l >> v[i].r;
        v[i].idx = i;
        nums[i * 2] = (v[i].l);
        nums[i * 2 + 1] = (v[i].r);
    }
    sort(nums.begin(), nums.end());
    int it = unique(nums.begin(), nums.end()) - nums.begin();
    nums.resize(it);
    int curpos = 0;
    unordered_map<int, int> pos;
    for (auto i : nums) {
        pos[i] = curpos++;
    }

    sz = curpos + 1;
    for (int i = 0; i < n; ++i) {
        update(0, 0, sz, pos[v[i].l], pos[v[i].r] + 1, 1);
    }

    int curb = t[0].first;
    for (int i = 0; i <= curb; ++i) {
        ans[i] = 0;
    }
    vector<s> v1 = v, v2 = v;
    sort(v1.begin(), v1.end(), comp1);
    sort(v2.begin(), v2.end(), comp2);

    int i1 = n - 1, i2 = n - 1;
    int cnt = 1;
    while (curb != n) {
        bool f = 0;
        while (used[v1[i1].idx]) {
            i1--;
            if (i1 == -1) {
                f = 1;
                break;
            }
        }
        while (used[v2[i2].idx]){
            i2--;
            if (i2 == -1) {
                f = 1;
                break;
            }
        }
        if (f)
            break;
        s left = v1[i1], right = v2[i2];
        used[v1[i1].idx] = 1;
        used[v2[i2].idx] = 1;
        if (left.idx == right.idx) {
            continue;
        }
        update(0, 0, sz, pos[left.l], pos[left.r] + 1, -1);
        update(0, 0, sz, pos[right.l], pos[right.r] + 1, -1);
        int ll = pos[left.l], lr = pos[left.r],
            rl = pos[right.l], rr = pos[right.r];
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

    //rebuild(0, 0, sz);
    for (auto &i : t) {
        i.first = 0;
        i.second = 0;
    }
    for (int i = 0; i < n; ++i) {
        update(0, 0, sz, pos[v[i].l], pos[v[i].r] + 1, 1);
    }
    for (int i = 0; i <= n; ++i)
        used[i] = 0;

    cnt = 1;
    curb = t[0].first;
    i1 = 0, i2 = 0;
    while (curb != n) {
        bool f = 0;
        while (used[v1[i1].idx]) {
            i1++;
            if (i1 == n) {
                f = 1;
                break;
            }
        }
        while (used[v2[i2].idx]){
            i2++;
            if (i2 == n) {
                f = 1;
                break;
            }
        }
        if (f)
            break;
        s left = v1[i1], right = v2[i2];
        used[v1[i1].idx] = 1;
        used[v2[i2].idx] = 1;
        if (left.idx == right.idx) {
            continue;
        }
        update(0, 0, sz, pos[left.l], pos[left.r] + 1, -1);
        update(0, 0, sz, pos[right.l], pos[right.r] + 1, -1);
        int ll = pos[left.l], lr = pos[left.r],
            rl = pos[right.l], rr = pos[right.r];
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


    while (q--) {
        int k;
        cin >> k;
        //if (ans[k] == INF && k == n)
        //    return -1;
        cout << ans[k] << " ";
    }
}

/*

4 4
1 10
2 3
4 5
1 20
1 2 3 4

*/

