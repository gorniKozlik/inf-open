//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2")
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <queue>
#include <deque>
#include <random>
#include <ctime>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vvll = vector<vll>;
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

void in(vll& a) {
	for (ll& i : a) cin >> i;
}

void out(vll& a) {
	for (ll& i : a) cout << i << ' ';
	cout << '\n';
}

void out(vvll& a) {
	for (ll i = 0; i < a.size(); ++i) {
		for (ll j = 0; j < a[0].size(); ++j) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}

void in(vpll& a) {
	for (pll& i : a) cin >> i.first >> i.second;
}

void in(vvll& a) {
	for (auto& v : a) {
		for (auto& x : v) cin >> x;
	}
}

void solve() {
	ll n, q; cin >> n >> q;
	vpll a(n);
	vll qs(q);
	in(a), in(qs);
	sort(all(qs));
	for (ll k : qs) {
		cout << max(1ll, k - 1) << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll ts = 1;
	//cin >> ts;
	while (ts--) solve();
}