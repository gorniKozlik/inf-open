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
		out << i << ' ';
	}
	return out;
}

const ll MOD = 998'244'353;
const ll INF = 1E18;

void solve() {
	ll n, q; cin >> n >> q;
	vector<pair<ll, ll>> strings(n);
	cin >> strings;
	vector<ll> k(q); cin >> k;
	for (ll i : k) {
		cout << (i) / 2 << ' ';
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
