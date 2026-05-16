#include<bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) (x).begin(), (x).end()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
const char nl = '\n';

template<typename T>
istream &operator>> (istream& in, vector<T>& a) {
    for (auto &el : a) in >> el;
    return in;
}

template<typename T>
ostream& operator<< (ostream& out, vector<T> &a) {
    for (auto &el : a) out << el << ' ';
    return out;
}

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;

    vector<int> q(m);
    cin >> q;
    for (auto el : q)
        cout << el / 2 << ' ';
}
