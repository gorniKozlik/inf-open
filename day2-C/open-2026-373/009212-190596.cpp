// C

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <complex>
#include <stdlib.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <cstring>
#include <string.h>
#include <math.h>
#include <cmath>
#include <chrono>
#include <random>
#include <float.h>
#include <cfloat>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sq(x) (x) * (x)
#define cube(x) (x) * (x) * (x)
using ll = long long;
using db = long double;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const ll LINF = 1LL << 62;
const db EPS = 1e-9;
using namespace std;

ll binpow(ll x, ll n) {
	if (!n) {
		return 1;
	}
	ll bp = binpow(x, n >> 1);
	if (n & 1)
		return (((bp * bp) % MOD) * x) % MOD;
	return (bp * bp) % MOD;
}

struct seg_tree {};
struct DSU {};
struct sparse_table {};
struct fenwick {};

inline void solve() {

	int n, k;
	cin >> n >> k;

	vector <pair<int, int>> vec;
	vector <int> st, end;
	vector <int> right;
	vector <int> left;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		vec.push_back({ a, 1 });
		vec.push_back({ b, -1 });
		right.push_back(b);
		left.push_back(a);
	}
	sort(all(vec));
	sort(rall(left));
	sort(all(right));
	vector <int> res(k, INF);
	vector <int> ans(3001, INF);

	for (int i = 0; i < k; i++) {
		int q; cin >> q;
		if (ans[q] == INF) {

			int l = -1, r = -1;
			int best = 0;
			for (int j = 0; j < 2 * n; j++) {
				
				if (vec[j].second == -1) {
					r = vec[j].first;
					int l_ = l, r_ = r;
					int best_ = best;
					int c = 0;
					int posl = 0;
					int posr = 0;
					while (best_ < q) {
						int ll = left[posl];
						int rr = right[posr];
						if (ll < rr || ll < l_ || rr > r_ || (rr == l_ && ll == r_)) {
							break;
						}
						posl++;
						posr++;

						if (ll > r_ && rr < l_) {
							best_ += 2;
						}
						else {
							best_++;
							if (rr == r_) {
								l_ = r_;
								r_ = right[posr];
							}
							else if (ll == l_) {
								r_ = l_;
								l_ = left[posl];
							}
						}
						c++;
					}
					if (best_ >= q) {
						res[i] = min(res[i], c);
						ans[q] = min(ans[q], c);
					}

					best--;
				}
				else {
					l = vec[j].first;
					best++;
				}
			}
		}
		else {
			res[i] = ans[q];
		}
	}

	for (int i = 0; i < k; i++) {
		cout << res[i] << " ";
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout.setf(ios_base::fixed); cout.precision(8);

	solve();
	return 0;
}