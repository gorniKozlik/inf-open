#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int ll, rr;
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, k;
    cin >> n >> q;
    vector <node> A(n);
    vector <int> l(n), r(n);
    for (int i=0; i<n; ++i) {
        cin >> A[i].ll >> A[i].rr;
    }
    vector <int> B(0);
    for (int i=3; i<n+1000000; i+=2) {
        B.push_back(i);
    }
    map<int, int> M;
    int x=2;
    for (auto c: B) {
        M[c]=c-x;
        ++x;
    }
    while (q--) {
        cin >> k;

        int w=B[lower_bound(B.begin(), B.end(), k)-B.begin()-2];
        cout << M[w] << ' ';
    }
    return 0;
}