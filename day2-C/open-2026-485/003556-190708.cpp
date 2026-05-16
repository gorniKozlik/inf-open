#include <bits/stdc++.h>
#define int long long

using namespace std;

vector<int> cnt;

vector<int> tree(2000000);

void build(int v,int l,int r) {
    if (r - l == 1) {
        tree[v] = cnt[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

int get(int v,int l,int r,int ql,int qr) {
    if (l >= ql && r <= qr) {
        return tree[v];
    }
    if (r <= ql || l >= qr) {
        return -1;
    }
    int m = (l + r) / 2;
    return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > A;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        A.push_back({l, 0});
        A.push_back({r, 1});
    }
    sort(A.begin(), A.end());

    int open = 0;
    for (auto i: A) {
        if (i.second == 0) {
            open++;
            cnt.push_back(open);
        } else {
            open--;
            cnt.push_back(open);
        }
    }
    cnt.pop_back();
    int N = cnt.size();
    build(0, 0, N);
    /*
        for (auto i:cnt) {
            cout<<i<<" ";

        }
        cout<<endl;
    */
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;

        //cout<<k-1<<" "<<N-k+1<<endl;
        int ans = get(0, 0, (int) cnt.size(), k - 1, N - k + 1);
        ans = max(0LL, k - ans);
        cout << ans / 2 + ans % 2 << " ";
    }
    cout << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
