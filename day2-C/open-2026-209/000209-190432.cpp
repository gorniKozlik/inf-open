#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <iomanip>
#define int long long
using namespace std;


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q; cin >> n >> q;
	vector<int> l(n), r(n);
	vector<int> a;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		a.push_back(l[i]);
		a.push_back(r[i]);
	}
	while (q--) {
		int x; cin >> x;
		cout << x / 2 << '\n';
	}
}