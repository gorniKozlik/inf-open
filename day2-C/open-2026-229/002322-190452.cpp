#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


// order_of_key
// find_by_order
using namespace __gnu_pbds;
using namespace std;
using ll = long long;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, q; cin >> n >> q;

	for (ll i = 1; i <= n; i++) {
		ll l, r; cin >> l >> r;
	}



	while (q--) {
		ll k; cin >> k;

			cout << ((k - 1) / 2) + ((k - 1) % 2 != 0) << '\n';	
		


	}
}


