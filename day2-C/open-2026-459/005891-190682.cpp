#include <bits/stdc++.h>

//#pragma GCC optimize("Ofast", "O3", "unroll-loops")
//#pragma GCC target ("avx2", "bmi", "bmi2")

using namespace std;
const int MAXN = 4e5 + 1;
const int INF = 1e9 + 7;

struct node {
    int mx = 0, to_add = 0;
};
int sz;
vector<node> t;

void push(int v) {
    t[v].mx += t[v].to_add;

    if (v * 2 + 2 < 4 * sz) {
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
    return (a.l > b.l || (a.l == b.l && a.r > b.r));
}
bool comp2(s a, s b) {
    return (a.r < b.r || (a.r == b.r && a.l < b.l));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

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
    /*
    cout << it << '\n';;
    for (auto i : nums)
        cout << i << " ";
    cout << '\n';
    */


    int curpos = 0;
    unordered_map<int, int> pos;
    for (auto i : nums) {
        pos[i] = curpos++;
    }

    sz = curpos + 1;
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

    vector<int> ans(n + 1, INF);
    for (int i = 0; i <= curb; ++i) {
        ans[i] = 0;
    }
    vector<s> v1 = v, v2 = v;
    sort(v1.begin(), v1.end(), comp1);
    sort(v2.begin(), v2.end(), comp2);

    int i1 = n - 1, i2 = n - 1;
    /*
    cout << "1: ";
    for (auto i : v1)
        cout << i.idx << " ";
    cout << '\n';
    cout << "2: ";
    for (auto i : v2)
        cout << i.idx << " ";
    cout << '\n';
    */
    vector<int> used(n + 1);
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
        //cout << "! " << v1[i1].idx << " " << v2[i2].idx << '\n';

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

        for (int i = curb + 1; i <= t[0].mx; ++i) {
            ans[i] = min(ans[i], cnt);
        }
        if (curb != t[0].mx)
            cnt++;
        curb = t[0].mx;
    }


    while (q--) {
        int k;
        cin >> k;

        cout << ans[k] << " ";
    }
}

/*

10 1
1 10
2 3
4 5
6 7
8 9
1 20
1 2
5 10
6 10
7 10

4 4
1 10
2 3
4 5
1 20
1 2 3 4

1 2
5 10
6 10
7 10

*/
