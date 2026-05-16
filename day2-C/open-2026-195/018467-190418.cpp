#include <bits/stdc++.h>
using T=long long;
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    T n,i,m,x,k,l,r,e,q,z,c,f;
    cin >> n >> q;
    vector<vector<T>>C;
    for (i=0;i<n;i++){
        cin >> l >> r;
        C.push_back({l,-1});
        C.push_back({r,1});
    }
    sort(C.begin(),C.end());
    vector<T>K(q);
    for (i=0;i<q;i++) cin >> K[i];
    l=0;
    r=n;
    k=0;
    z=n;
    map<T,T>D;
    set<T>E;
    for (auto e:C){
        c=e[0];
        f=e[1];
        D[k]=max(D[k],min(l,r));
        E.insert(k);
        if (f==-1){
            k+=1;
            r-=1;
        }
        else{
            k-=1;
            l+=1;
        }
        D[k]=max(D[k],min(l,r));
        E.insert(k);
    }
    vector<vector<T>>U;
    for (auto d:E){
        U.push_back({d+D[d]*2,d,D[d]});
    }
    sort(U.begin(),U.end());
    n=U.size();
    vector<T>F(n);
    F[n-1]=U[n-1][1];
    for (i=n-2;i>-1;i--)
        F[i]=max(F[i+1],U[i][1]);
    for (auto k:K){
        l=-1;
        r=n-1;
        while (l<r-1){
            m=(l+r)/2;
            if (U[m][1]+U[m][2]*2<k)
                l=m;
            else
                r=m;
        }
        cout << max((T)0,k-F[r]+1)/2 << " ";
    }

    return 0;
}
