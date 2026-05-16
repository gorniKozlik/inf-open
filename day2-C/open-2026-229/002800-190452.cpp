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

	
	vector <pair <ll, ll>> sk;



	for (ll i = 1; i <= n; i++) {
		ll l, r; cin >> l >> r;
		sk.push_back({l, 1});
		sk.push_back({r, -1});
	}

	sort(sk.begin(), sk.end());

	ll cur = 0;

	ll mx = 0;
	for (auto el : sk) {
		cur += el.second;
		mx = max(mx, cur);
	}



	while (q--) {
		ll k; cin >> k;

		if (k <= mx) {
			cout << 0 << '\n';
		} else {
			cout << (k - mx) / 2 + ((k - mx) % 2 != 0) << '\n';
		}


	}
}


