#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<ll, ll>;

const ll INF = 1000000001;
const ll MOD = 998244353;
const ll INF2 = 1e18;

mt19937 rnd(0);

template<typename T>
istream& operator>>(istream& in, vector<T>& a) {
	for (auto& x : a) {
		in >> x;
	}
	return in;
}

template<typename T>
ostream& operator<<(ostream& out, vector<T>& a) {
	for (auto& x : a) {
		out << x << ' ';
	}
	return out;
}

void solve() {
	ll n, q;
	cin >> n >> q;
	vector<pii> arr;
	vector<ll> all;
	for (ll i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		arr.push_back({ l, -1 });
		arr.push_back({ r, 1 });
		all.push_back(l);
		all.push_back(r);
	}
	sort(all.begin(), all.end());
	map<ll, ll> mp;
	for (ll i = 0; i < 2 * n; i++) {
		mp[all[i]] = i;
	}
	for (auto& it : arr) {
		it.first = mp[it.first];
	}
	sort(arr.begin(), arr.end());
	vector<ll> a(2 * n, 0);
	ll cursum = 0;
	for (ll i = 0; i < 2 * n; i++) {
		cursum -= arr[i].second;
		a[i] = cursum;
	}
	vector<ll> ans(n, 0);
	ll curmax = a[n - 1];
	for (ll i = n; i >= 1; i--) {
		ans[i - 1] = (max(0, i - curmax) + 1) / 2;
		if (i >= 2) {
			curmax = max({ curmax, a[i - 2], a[i + 1] });
		}
	}
	for (ll i = 0; i < q; i++) {
		ll k;
		cin >> k;
		cout << ans[k - 1] << '\n';
	}
}

void precalc() {
	return;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll t_ = 1;
	//cin >> t_;
	precalc();
	ll i = 0;
	while (i < t_) {
		solve();
		i++;
	}
	return 0;
}