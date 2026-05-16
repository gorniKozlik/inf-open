#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

const int mod = 998244353;
const ll inf = 1e18;
const int INF = 1e9;

#define vec vector
#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define rev reverse
#define umap unordered_map
#define pll pair<ll, ll>
#define pii pair<int, int>
#define len(a) int(a.size())
#define pb push_back

void solve() {
	int n, q;
	cin >> n >> q;
	vec<pll> a(n);
	vec<ll> x;
	for (int i = 0; i < n; i++) {
		cin >> a[i].ff >> a[i].ss;
		x.pb(a[i].ff), x.pb(a[i].ss);
	}
	sort(all(x));
	x.erase(unique(all(x)), x.end());
	vec<int> cur(n + 1, INF);
	for (int i = 0; i < len(x); i++) {
		int c = 0, c1 = 0, c2 = 0;
		for (auto par : a) {
			ll l = par.ff, r = par.ss;
			if (l <= x[i] && x[i] <= r) c++;
			if (r < x[i]) c1++;
			if (l > x[i]) c2++;
		}
		for (int i = 1; i <= c; i++) cur[i] = min(cur[i], 0);
 		int mx = c + 2 * min(c1, c2);
		for (int i = c + 1; i <= mx; i++) {
			cur[i] = min(cur[i], (i - c) / 2 + (i - c) % 2);
		}
		int ans = min(c1, c2);
		for (int i = mx + 1; i <= n; i++){
			cur[i] = min(cur[i], ans + (i - mx));
		}
	}
	while (q--) {
		int k;
		cin >> k;
		cout << cur[k] << "\n";
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int test = 1;
	// cin >> test;
	while (test--) {
		solve();
	}
}