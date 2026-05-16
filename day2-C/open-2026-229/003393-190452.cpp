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

	unordered_map <ll, ll> comp;
	unordered_map <ll, ll> merge;
	


	vector <pair <ll, ll>> sk;

	vector <ll> vals;

	for (ll i = 1; i <= n; i++) {
		ll l, r; cin >> l >> r;
		vals.push_back(l);
		vals.push_back(r);
		sk.push_back({l, r});
	}


	sort(vals.begin(), vals.end());
	ll cur = 1;


	for (auto el : vals) { comp[el] = cur++; }
	cur--;


	ll cnt = 
	for (auto el : sk) {
		ll l = comp[el.first];
		ll r = comp[el.second];
		merge[l] = r;
		merge[r] = l;
	}

	ll answer = 0;


	for (ll i = 1; i <= cur / 2; i++) {
		if (merge[i] != (n - i + 1)) {
			answer++;
			ll frst = merge[n - i + 1];
			ll scnd = merge[i];
			merge[i] = n - i + 1;
			merge[n - i + 1] = i;
			merge[frst] = scnd;
			merge[scnd] = frst;
		}
	}



	while (q--) {
		ll k; cin >> k;

		cout << answer << '/n';
	}
}


