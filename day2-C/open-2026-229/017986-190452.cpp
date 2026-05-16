


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

	vector <pair <ll, ll>> scanline;
	for (auto &el : sk) {
		ll l = comp[el.first];
		ll r = comp[el.second];
		merge[l] = r;
		merge[r] = l;
		scanline.push_back({l, 1});
		scanline.push_back({r, -1});
	}

	sort(scanline.begin(), scanline.end());
	vector <ll> answers(n + 1, 0);
	for (ll i = 1; i <= n; i++) { answers[i] = ((i - 1) / 2 + ((i - 1) % 2 != 0)); }


	ll best = 0;

	ll closed = 0;
	cur = 0;

	vector <pair <ll, ll>> segs;

	for (auto el : scanline) {
		if (el.second == -1) {
			closed++;
		}
		cur += el.second;
		ll left = closed;

		ll right = n - closed - cur;

		ll max_add = min(left, right) * 2;

		best = max(cur, best);


		if (max_add != 0) {
			segs.push_back({cur + 1, cur + max_add});
		}

		// for (ll i = 1; i <= max_add && (cur + i) <= n; i++) {
		// 	answers[cur + i] = min(answers[cur + i], ((i) / 2) + ((i) % 2 != 0));
		// }
	}
	

	sort(segs.begin(), segs.end());



	set <pair <ll, ll>> doin;

	ll ind = 0;
	for (ll i = best + 1; i <= n; i++) {
		while (ind < segs.size() && segs[ind].first <= i) {
			doin.insert(segs[ind]);
			ind++;
		}


		while (!doin.empty() && (*(--doin.end())).second < i) {
			doin.erase(--doin.end());
		}



		if (!doin.empty()) {
			answers[i] = min(answers[i],  (i - (*(--doin.end())).first + 1) / 2 + (i - (*(--doin.end())).first + 1) % 2      );
		}
	}


	for (ll i = 0; i <= best; i++) { answers[i] = 0; }

	while (q--) {
		ll k; cin >> k;
		cout << answers[k] << ' ';
	}
}


