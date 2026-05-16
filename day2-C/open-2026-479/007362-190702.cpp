#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//#define int int64_t
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define pii pair<int, int>
#define vpi vector<pii>
#define vb vector<bool>
#define umap unordered_map
using namespace std;
//using namespace __gnu_pbds;
mt19937 rng(333);
//template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//template<class T> using omset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
void solve() {
	int n, q; cin >> n >> q;
	vi p(2*n-1, 0);
	vpi B(n*2, {0, 0});
	
	for (int i=0; i<n; ++i) {
		cin >> B[i*2].first >> B[i*2+1].first;
		B[i*2].second = 1;
		B[i*2+1].second = -1;
	}
	sort(B.begin(), B.end());
	int c=0;
	for (int i=0; i<2*n-1; ++i) {
		c += B[i].second;
		p[i] = c;
	}
	vi ans(n+1, 0);
	int m = p[n-1];
	ans[n] = (n-m+1)/2;
	for (int i=1; i<n; ++i) {
		cout << i << endl;
		m = max(m, max(p[n-1-i], p[n-1+i]));
		ans[n-i] = max(0, (n-i-m+1)/2);
	}
	int x;
	for (int i=0; i<q; ++i) {
		cin >> x;
		cout << ans[x] << ' ';
	}
	cout << '\n';
}
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t=1; //cin >> t;
	while (t--) solve();
	return 0;
}
