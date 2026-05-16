#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()

using namespace std;
typedef long long ll;

const ll mod = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0, x, y; i < n; ++i)
        cin >> x >> y;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (x <= 3)
            cout << "1 ";
        else
            cout << x / 2 + x % 2 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    return 0;
}
