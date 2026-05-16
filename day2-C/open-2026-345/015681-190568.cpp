#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC target("avx2,avx,popcnt,lzcnt,sse4.2,sse4.1,sse4")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
typedef pair<int, int> xt;
#define x first
#define t second

int main() {
	cout.tie(0);
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<xt> a(n*2);
	for (int i = 0; i < n; ++i) {
		int l, r;
		cin >> l >> r;
		a[2*i] = {l, +1};
		a[2*i+1] = {r, -1};
	}
	sort(a.begin(), a.end(), [](const xt& a, const &xt b) { return a.x < b.x || (a.x == b.x && a.t > b.t); });
	vector<xt> p(n+1, -1);
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		p[k] = i;
	}
	// no intersections
	int ops = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i].t != +1 || a[2*n-i] != -1) {
			ops++;
		}
		p[i+1] = ops;
	}
	vector<int> ans(q);
	for (int i = 0; i <= n; ++i) {
		if (p[i] == -1) continue;
		ans[p[i]] = i;
	}
	for (int i = 0; i < q; ++i) {
		cout << ans[i] << ' ';
	}
	cout << '\n';

	return 0;
}
