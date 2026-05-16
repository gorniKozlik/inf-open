#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <set>
#include <stack>

using namespace std;
using ll = long long;

istream& operator>>(istream& in, pair<ll, ll>& a) {
	return in >> a.first >> a.second;
}

template <class T>
istream& operator>>(istream& in, vector<T>& a) {
	for (T& i : a) {
		in >> i;
	}
	return in;
}

template <class T>
ostream& operator<<(ostream& out, vector<T>& a) {
	for (T& i : a) {
		out << i;
	}
	return out;
}

const ll MOD = 998'244'353;
const ll INF = 1E18;

void solve() {
	ll n, q; cin >> n >> q;
	vector<pair<ll, ll>> events;
	for (ll i = 0; i < n; i++) {
		ll l, r; cin >> l >> r;
		events.push_back({ l, 1 });
		events.push_back({ r + 1, -1 });
	}
	sort(events.begin(), events.end());

	ll cnt = 0;
	ll cnt_best = 0;
	for (ll i = 0; i < 2 * n; i++) {
		cnt += events[i].second;
		cnt_best = max(cnt, cnt_best);
	}
	while (q--) {
		ll k; cin >> k;
		cout << max(0ll, k - cnt_best) << ' ';
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);

	ll t = 1;
	//cin >> t;
	while (t--) {
		solve();
		cout << '\n';
	}
}
