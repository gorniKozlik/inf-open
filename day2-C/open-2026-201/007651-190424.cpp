// #include <bits/stdc++.h>
// #pragma optimize("Ofast")
// #pragma optimize("O3")

// using namespace std;

// using ll = long long;

// const int INF = 1e9 + 7, mod = 998244353;

// #ifdef LOCAL
// const int MAXN = 1e2, MAXK = 2001;
// #else
// const int MAXN = 1e6, MAXK = 2001;
// #endif

// vector<int> tree, cnt;

// void build(int i, int l, int r) {
//     if (l + 1 == r) {
//         tree[i] = cnt[l];
//         return;
//     }
//     int m = (l + r) / 2;
//     build(2 * i + 1, l, m);
//     build(2 * i + 2, m, r);
//     tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
// }

// int get(int i, int l, int r, int ql, int qr) {
//     if (qr <= l || r <= ql)
//         return 0;
//     if (ql <= l && r <= qr)
//         return tree[i];
//     int m = (l + r) / 2;
//     return max(get(2 * i + 1, l, m, ql, qr), get(2 * i + 2, m, r, ql, qr));
// }

// int main() {
// #ifdef LOCAL
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
//     int n, q;
//     cin >> n >> q;
//     vector<pair<int, int>> lines(n);
//     vector<int> x, sm(2 * n + 10), cls(2 * n + 10), dop(2 * n + 10);
//     for (pair<int, int> &i : lines) {
//         cin >> i.first >> i.second;
//         x.push_back(i.first);
//         x.push_back(i.second);
//     }
//     sort(x.begin(), x.end());
//     for (pair<int, int> &i : lines) {
//         i.first = lower_bound(x.begin(), x.end(), i.first) - x.begin();
//         i.second = lower_bound(x.begin(), x.end(), i.second) - x.begin();
//         sm[i.first]++;
//         sm[i.second + 1]--;
//         cls[i.second + 1]++;
//         if (i.first)
//             dop[i.first - 1]++;
//     }
//     for(int i = 1; i < 2 * n + 10; i++)
//         cls[i] += cls[i - 1];
//     for(int i = 2 * n + 8; i >= 0; i--)
//         dop[i] += dop[i + 1];
//     for(int i : cls) cout << i << ' ';
//     cout << '\n';
//     for(int i : dop) cout << i << ' ';
//     cout << '\n';
//     vector<int> ans(n + 1, INF);
//     for (int i = 1; i <= n; i++) {
//         int now = 0, close = 0;
//         for (int j = 0; j < 2 * n; j++) {
//             now += sm[j];
//             cout << i << ' ' << x[j] << ' ' << now << ' ' << cls[j] << ' ' << dop[j] << '\n';
//             if (2 * cls[j] < max(i - now, 0) || 2 * dop[j] < max(i - now, 0))
//                 continue;
//             ans[i] = min(ans[i], max(0, i - now + 1) / 2);
//         }
//     }
//     while (q--) {
//         int k;
//         cin >> k;
//         cout << ans[k] << ' ';
//     }
//     return 0;
// }

//                    {{{{{{
//                    {{{{{
//                ____{____     MEGAKNIGHT!!!
//               /         \  //
//              /  ==   ==  \//
//              |           |
//   __^__     ----------------      __^__
//  /     \    |              |     /     \
// <       >   |              |    <       >
//  \     /_____               _____\     /


#include <bits/stdc++.h>
#pragma optimize("Ofast")
#pragma optimize("O3")

using namespace std;

using ll = long long;

const int INF = 1e9 + 7, mod = 998244353;

#ifdef LOCAL
const int MAXN = 1e2, MAXK = 2001;
#else
const int MAXN = 1e6, MAXK = 2001;
#endif

vector<int> tree, cnt;

void build(int i, int l, int r){
    if(l + 1 == r){
        tree[i] = cnt[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * i + 1, l, m);
    build(2 * i + 2, m, r);
    tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
}

int get(int i, int l, int r, int ql, int qr) {
    if(qr <= l || r <= ql)
        return 0;
    if(ql <= l && r <= qr) return tree[i];
    int m = (l + r) / 2;
    return max(get(2 * i + 1, l, m, ql, qr), get(2 * i + 2, m, r, ql, qr));
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> lines(n);
    vector<int> x, sm(2 * n + 10);
    for (pair<int, int> &i : lines){
        cin >> i.first >> i.second;
        x.push_back(i.first);
        x.push_back(i.second);
    }
    sort(x.begin(), x.end());
    for (pair<int, int> &i : lines){
        i.first = lower_bound(x.begin(), x.end(), i.first) - x.begin();
        i.second = lower_bound(x.begin(), x.end(), i.second) - x.begin();
        sm[i.first]++;
        sm[i.second + 1]--;
    }
    int now = 0;
    cnt.resize(2 * n + 10);
    tree.resize(10 * n);
    for(int i = 0; i < 2 * n + 10; i++){
        now += sm[i];
        cnt[i] = now;
    }
    build(0, 0, 2 * n);
    for(int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int now = get(0, 0, n, k - 1, 2 * n - k + 1);
        cout << max(0, (k - now + 1) / 2) <<' ';
    }
    return 0;
}

//                    {{{{{{
//                    {{{{{
//                ____{____     MEGAKNIGHT!!!
//               /         \  //
//              /  ==   ==  \//
//              |           |
//   __^__     ----------------      __^__
//  /     \    |              |     /     \
// <       >   |              |    <       >
//  \     /_____               _____\     /
