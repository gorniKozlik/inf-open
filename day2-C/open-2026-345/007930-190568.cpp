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


int main() {
	//cout.tie(0);
	//cin.tie(0);
	//ios::sync_with_stdio(0);
	int f, n, m;
	cin >> f >> n >> m;
	vector<int> a(n);
	bool all_even = true;
	bool all_odd = true;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		--a[i];
		if (a[i] % 2 == 0) {
			all_odd = false;
		} else {
			all_even = false;
		}
	}
	string dir;
	cin >> dir;
	cout << ((all_even || all_odd)? "Yes" : "No") << '\n';

	return 0;
}
