#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <random>
#include <cmath>

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC target("popcnt")

#define int long long
#define all(a) a.begin(),a.end()
#define endl '\n'
#define pii pair<int, int>
#define pb emplace_back
typedef long double ld;

int const N = 2e6, M = 1e2 + 5, lg = 23, INF = 2e9;
int mod = 998244353, mod2 = 1e9 + 9;
int P = 1e9 + 7;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	multiset<pii> l, r;

	int n, q; cin >> n >> q;

	for (int i = 0; i < n; ++i) {
		int a, b; cin >> a >> b;
		r.insert({ a, b });
		l.insert({ b, a });
	}

	vector<int> k(q);
	for (int& i : k) cin >> i;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		pii a = *l.begin();
		pii b = *r.rbegin();
		if (a == b) continue;
		if (a.first < b.first) ans++;
		l.erase(l.begin());
		r.erase(--r.end());
	}

	cout << ans;

	return 0;
}