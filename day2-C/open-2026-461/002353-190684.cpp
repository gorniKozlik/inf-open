#pragma GCC optimize("O3")
#include <vector>

#pragma GCC target("avx2")
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <set>
#include <map>

using namespace std;

#define ll long long
#define ld long double
#define pll pair<ll, ll>
#define pld pair<ld, ld>

#define vll vector<ll>
#define vvll vector<vll>
#define vvvll vector<vvll>
#define vvvvll vector<vvvll>

#define vld vector<ld>
#define vvld vector<vld>
#define vvvld vector<vvld>
#define vvvvld vector<vvvld>

#define vpll vector<pll>
#define vvpll vector<vpll>
#define vvvpll vector<vvpll>
#define vvvvpll vector<vvvpll>

#define vpld vector<pld>
#define vvpld vector<vpld>
#define vvvpld vector<vvpld>
#define vvvvpld vector<vvvpld>

#define forlr(i, l, r) for(ll i = (l); i < (r); ++i)
#define forn(i, n) forlr(i, 0, n)
#define forin(x, v) for(auto& x : v)

#define all(v) v.begin(), v.end()
#define pb emplace_back

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
	forin(x, v)
		in >> x;
	return in;
}

template <class T>
ostream& operator<<(ostream& out, vector<T>& v) {
	forin(x, v)
		out << x << ' ';
	return out;
}

vll us;

ll cnt(vpll lr) {
	ll n = lr.size();
	us = vll(n);

	vpll p;
	for (auto [l, r] : lr) {
		p.pb(l, 1);
		p.pb(r, -1);
	}
	sort(all(p));

	ll ans = 0, at = 0, ax = -1;
	for (auto& [x, d] : p) {
		at += d;
		if (at > ans) {
			ans = at;
			ax = x;
		}
	}

	ll ay = -1;
	for (auto [l, r] : lr) {
		if (l == ax)
			ay = r;
	}

	forn(i, n) {
		us[i] = 
			lr[i].first <= ax && ax <= lr[i].second ||
			lr[i].first <= ay && ay <= lr[i].second;
	}
	return ans;
}

vll main0(vpll lr) {
	ll n = lr.size();
	vll ans(n + 1);
	ll ai = 0, t = cnt(lr), at = 0;
	while (ai <= t) {
		ans[ai++] = at;
	}

	vpll rs(n), ls(n);
	forn(i, n) {
		ls[i] = { lr[i].first, i };
		rs[i] = { lr[i].second, i };
	}
	sort(all(ls));
	reverse(all(ls));
	sort(all(rs));

	while (ai <= n) {
		ll li = 0, ri = 0;
		forn(i, n) { // sort
			if (lr[i].second < lr[li].second)
				li = i;
			if (lr[i].first > lr[ri].first)
				ri = i;
		}

		assert(li != ri);

		swap(lr[li].second, lr[ri].first);
		//swap(lr[li].second, lr[ri].second);
		//swap(lr[ri].first, lr[ri].second);

		//t = cnt(lr); // ?dp
		t += 2 - us[li] - us[ri];
		us[li] = us[ri] = 1;
		++at;
		while (ai <= t) {
			ans[ai++] = at;
		}
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _LOCAL
	while (1)
#endif // _LOCAL
	{
		ll t = 1;
		//cin >> t;
		while (t--) {
			ll n, q;
			cin >> n >> q;
			vpll lr(n);
			for (auto& [l, r] : lr)
				cin >> l >> r;

			vll ans = main0(lr);

			while (q--) {
				ll x;
				cin >> x;
				cout << ans[x] << ' ';
			}
			cout << endl;
		}
	};
}
