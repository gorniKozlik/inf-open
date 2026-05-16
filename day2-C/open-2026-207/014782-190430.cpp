#include <bits/stdc++.h>
#define ll long long
#define int long long
#define pii pair<int, int>
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define pb push_back
using namespace std;

int l[200'010];
int r[200'010];

void solve() {
    int n, q;
    cin >> n >> q;
    for  (int i = 1; i <= n; i++)
        cin >> l[i] >> r[i];
    while (q--) {
        int k;
        cin >> k;
        cout << k - 1 << endl;
    }
    return;
}

int32_t main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}

