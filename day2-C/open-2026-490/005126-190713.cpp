#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
    int ll, rr;
};
int f(vector <node> A) {
    unordered_map<int, int> M;
    for (int i=0; i<A.size(); ++i) {
        for (int j=A[i].ll; j<=A[i].rr; ++j) {
            M[j]++;
        }
    }
    int ans=0;
    for (auto c: M) {
        ans=max(ans, c.second);
    }
    return ans;
}
bool key(node a, node b) {
    return (abs(a.rr-a.ll)>abs(b.rr-b.ll));
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, k;
    cin >> n >> q;
    vector <node> A(n);
    vector <int> l(n), r(n);
    for (int i=0; i<n; ++i) {
        cin >> A[i].ll >> A[i].rr;
        l[i]=A[i].ll, r[i]=A[i].rr;
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    while (q--) {
        cin >> k;
        int kk=f(A);
        if (kk>=k) {
            cout << 0;
            return 0;
        } else {
            int ans=1;
            for (int i=0; i<n; ++i) {
                int a1=l.back(), a2=r.back();
                l.pop_back(), r.pop_back();
                node res1, res2;
                for (int ii=0; ii<n; ++ii) {
                    if (A[ii].ll==a1) res1=A[ii];
                    if (A[ii].rr==a2) res2=A[ii];
                }
                if (res1.ll==res2.ll && res2.rr==res1.rr) {
                    continue;
                }
                vector <node> AA(0);
                for (int ii=0; ii<n; ++ii) {
                    if (A[ii].ll!=res1.ll && A[ii].rr!=res1.rr && A[ii].rr!=res2.rr && A[ii].ll!=res2.ll) {
                        AA.push_back(A[ii]);
                    }
                }
                swap(res1.rr, res2.rr);
                AA.push_back(res1), AA.push_back(res2);
                int K=f(AA);
                if (K>=k) {
                    cout << ans;
                    return 0;
                }
                ++ans;
                A=AA;
            }
        }
    }
    return 0;
}