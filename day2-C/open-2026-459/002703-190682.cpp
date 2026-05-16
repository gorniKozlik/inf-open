#include <bits/stdc++.h>

//pragma GCC optimize("Ofast", "O3", "unroll-loops")
//#pragma GCC target ("avx2", "bmi", "bmi2")

using namespace std;
const int MAXN = 4e5 + 1;
const int INF = 1e9 + 7;

struct node {
    int mx = 0, to_add = 0;
};
vector<node> t;

void push(int v) {
    t[v].mx += t[v].to_add;

    if (v * 2 + 2 < 4 * MAXN) {
        t[v * 2 + 1].to_add += t[v].to_add;
        t[v * 2 + 2].to_add += t[v].to_add;
    }
    t[v].to_add = 0;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        t[v].to_add += x;
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
    t[v].mx = max(t[v * 2 + 1].mx, t[v * 2 + 2].mx);
}

struct s {
    int l, r, idx;
};

bool comp1(s a, s b) {
    return a.l > b.l;
}
bool comp2(s a, s b) {
    return a.r < b.r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<s> v(n);

    set<int> nums;
    for (int i = 0; i < n; ++i) {
        cin >> v[i].l >> v[i].r;
        v[i].idx = i;
        nums.insert(v[i].l);
        nums.insert(v[i].r);
    }
    int curpos = 0;
    map<int, int> pos;
    for (auto i : nums) {
        pos[i] = curpos++;
    }

    int sz = nums.size();
    t.resize(4 * sz);
    for (int i = 0; i < n; ++i) {
        update(0, 0, sz, pos[v[i].l], pos[v[i].r] + 1, 1);
    }

    /*
    cout << "===segtree" << '\n';
    for (int i = 0 ; i < 25; ++i) {
        cout << i << ": " << t[i].mx << " " << t[i].to_add << '\n';
    }
    */

    int curb = t[0].mx;

    vector<int> ans(n + 1, -1);
    for (int i = 1; i <= curb; ++i) {
        ans[i] = 0;
    }
    vector<s> v1 = v, v2 = v;
    sort(v1.begin(), v1.end(), comp1);
    sort(v2.begin(), v2.end(), comp2);

    int i1 = n - 1, i2 = n - 1;

    int cnt = 1;
    while (curb != n && i1 >= 0 && i2 >= 0) {
        s left = v1[i1], right = v2[i2];
        i1--; i2--;
        if (left.idx == right.idx) {
            continue;
        }

        update(0, 0, sz, pos[left.l], pos[left.r] + 1, -1);
        update(0, 0, sz, pos[right.l], pos[right.r] + 1, -1);

        update(0, 0, sz, pos[left.l], pos[right.r] + 1, 1);
        update(0, 0, sz, pos[left.r], pos[right.l] + 1, 1);

        for (int i = curb + 1; i <= t[0].mx; ++i) {
            ans[i] = cnt;
        }
        cnt++;
        curb = t[0].mx;
    }


    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}
