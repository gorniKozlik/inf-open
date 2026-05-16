#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& out, vector<T> v) {
	for (T it : v) {
		out << it << ' ';
	}
	out << '\n';
	return out;
}

#define ll long long
#define pii pair<int, int>

const int MAX = 500'005;
const int LG = 24;
const int MOD = 998'244'353;

pii s[MAX];

int main()
{
	int n, q;
	cin >> n >> q;

	for (int i = 0; i < n; i++) {
		cin >> s[i].first >> s[i].second;
	}
	int k;
	for (int i = 0; i < q; i++) {
		cin >> k;
		cout << (k / 2) << ' ';
	}
}


