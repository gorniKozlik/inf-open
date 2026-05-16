#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#define int int64_t
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
	vi L(n, 0); vi R(n, 0);
	for (int i=0; i<n; ++i) {
		cin >> L[i] >> R[i];
		L[i]--;
		R[i]--;
	}
	int x;
	for (int i=0; i<q; ++i) {
		cin >> x;
		cout << 0 << '\n';
	}
}
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t=1; //cin >> t;
	while (t--) solve();
	return 0;
}
