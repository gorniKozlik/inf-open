#include <bits/stdc++.h>
using T=long long;
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    T n,i,m,x,k,l,r,e,q,z,c,f,K;
    cin >> n >> q;
    vector<vector<T>>C;
    for (i=0;i<n;i++){
        cin >> l >> r;
        C.push_back({l,-1});
        C.push_back({r,1});
    }
    sort(C.begin(),C.end());
    cin >> K;
    l=0;
    r=n;
    k=0;
    z=n;
    for (auto e:C){
        c=e[0];
        f=e[1];
        if (k+min(l,r)*2>=K)
            z=min(z,max((T)0,K-k+1)/2);
        if (f==-1){
            k+=1;
            r-=1;
        }
        else{
            k-=1;
            l+=1;
        }
        if (k+min(l,r)*2>=K)
            z=min(z,max((T)0,K-k+1)/2);
    }

    cout << z;
    return 0;
}
