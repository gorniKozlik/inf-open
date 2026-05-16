#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_set>
using namespace std;
#define int long long
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define ppb pop_back
const int maxn = 500, mod = 998244353, inf = 1e18;

void solve() {
	int n, q;
	cin >> n >> q;
	vector <pair<int, int>> a(n);
	for (auto& x : a)
		cin >> x.ff >> x.ss;
	while (q--) {
		int k;
		cin >> k;
		cout << k / 2 << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	//cin >> t;
	while (t--)
		solve();
}
