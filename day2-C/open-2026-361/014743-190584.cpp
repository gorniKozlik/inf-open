#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2")
#pragma GCC optimize("Ofast,unroll-loops")
#define int long long
using namespace std;
using ll = long long;
using ld = long double;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
/*ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}
vector<vector<int>> g;

void dfs(int u, int c, vector<char>& used, vector<int>& color) {
	used[u] = 1;
	color[u] = c;
	for (int v : g[u]) {
		if (!used[v]) {
			dfs(v, c, used, color);
		}
	}
}*/
vector<int> a, newa, cur, countn;
deque<int> wait;
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	return a.first < b.first;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> a(n);
	vector<int> tasks(q);
	for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
	for (int i = 0; i < q; ++i) cin >> tasks[i];
	sort(all(a));
	//for (int i = 0; i < n; ++i) cout << a[i].first << " " << a[i].second << "; ";
	//cout << "\n";
	pair<int, int> median = a[(n-1) / 2];
	int countinmedian = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] != median && !(a[i].second < median.first || a[i].first > median.second)) {
			countinmedian++;
			//cout << "XA! OTPE3OK " << a[i].first << " " << a[i].second << " BXODIT B MEDIANY " << median.first << " " << median.second << "!!!!!!\n";
		}
			
	}
	countinmedian /= 2;
	cout << n / 2 - countinmedian;
}