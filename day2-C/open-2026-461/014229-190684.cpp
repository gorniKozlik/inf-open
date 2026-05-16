#pragma GCC optimize("O3")
#include <vector>

#pragma GCC target("avx2")
#include <algorithm>
#include <random>
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

ll cnt(vpll lr, ll upd = 1) {
	ll n = lr.size();

	if(upd)
		us = vll(n);

	vpll p;
	for (auto [l, r] : lr) {
		p.pb(l, 1);
		p.pb(r, -1);
	}
	sort(all(p));

	ll ans = 0, at = 0, ax = -1;
	ll ay = -1;
	for (auto& [x, d] : p) {
		at += d;
		if (at > ans) {
			ans = at;
			ax = x;
		}
		else if (ay < ax && at - d == ans) {
			ay = x;
		}
	}

	if (upd) {
		forn(i, n) {
			us[i] =
				lr[i].first <= ax && ax <= lr[i].second;
		}
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

	if (0) { // g3
		t = 1;
		sort(all(lr));
		us = vll(n);
		us[lr.size() / 2] = 1;
	}

	if (0) { // g4; wa
		vll ans(n);
		ans.push_back((n - t + 1) / 2);
		return ans;
	}

	vpll rs(n), ls(n);
	forn(i, n) {
		ls[i] = { lr[i].first, i };
		rs[i] = { lr[i].second, i };
	}
	sort(all(ls));
	reverse(all(ls));
	sort(all(rs));

	auto lit = ls.begin();
	auto rit = rs.begin();

	while (ai <= n) {
		ll li = rit->second, ri = lit->second;
		++lit;
		++rit;

		/*forn(i, n) { // sort
			if (lr[i].second < lr[li].second)
				li = i;
			if (lr[i].first > lr[ri].first)
				ri = i;
		}*/

		swap(lr[li].second, lr[ri].first);
		//swap(lr[li].second, lr[ri].second);
		//swap(lr[ri].first, lr[ri].second);

		//t = cnt(lr); // ?dp
		t += 2 - us[li] - us[ri];
		us[li] = us[ri] = 1;
		//assert(t == cnt(lr));
		++at;
		while (ai <= t) {
			ans[ai++] = at;
		}
	}

	return ans;
}

vll main1(vpll lr) {
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

	auto lit = ls.begin();
	auto rit = rs.begin();

	while (ai <= n) {
		ll li = rit->second, ri = lit->second;
		++lit;
		++rit;

		swap(lr[li].second, lr[ri].first);
		t = cnt(lr); // ?dp

		++at;
		while (ai <= t) {
			ans[ai++] = at;
		}
	}

	return ans;
}

vll main4(vpll lr) {
	ll n = lr.size();
	if (n == 1)
		return { 0, 0 };
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

	auto lit = ls.begin();
	auto rit = rs.begin();

	auto f = [&](ll k) {
		auto lrt = lr;
		auto lit = ls.begin();
		auto rit = rs.begin();
		while (k--) {
			ll li = rit->second, ri = lit->second;
			++lit;
			++rit;
			if (li == ri)
				break;

			swap(lrt[li].second, lrt[ri].first);
		}
		return cnt(lrt);
	};

	vll res(n);
	ll l = -1, r = n;
	while (r - l > 1) {
		ll x = (l + r) / 2;
		(f(x) == n ? r : l) = x;
	}
	res.push_back(r);
	return res;
}

#ifdef _LOCAL
void tests() {
	mt19937 mt;

	ll t;
	cin >> t;

	ll n, mx;
	cin >> n >> mx;

	while (t--) {
		set<ll> s;
		vpll a;
		forn(i, n) {
			ll l = 0, r = 0;
			while (l >= r || s.contains(l) || s.contains(r)) {
				l = mt() % mx + 1;
				r = mt() % mx + 1;
			}
			s.insert(l);
			s.insert(r);
			a.pb(l, r);
		}
		if (main0(a) != main1(a)) {
			cout << "err\n";
			main0(a);
			main1(a);
		}
	}
	cout << "end\n";
}
#endif // _LOCAL

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _LOCAL
	while (1)
		//tests();
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

			vll ans = main4(lr);

			while (q--) {
				ll x;
				cin >> x;
				cout << ans[x] << ' ';
			}
			cout << endl;
		}
	};
}
