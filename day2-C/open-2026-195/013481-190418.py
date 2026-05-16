#include <bits/stdc++.h>
using T=int;
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    T n,i,m,x,k,l,r,e,q,z,c,f,K;
    cin >> n >> q;
    vector<vector<T>>C(2*n,vector<T>(2,0));
    for (i=0;i<n;i++){
        cin >> l >> r;
        C[i][0]=l;
        C[i][1]=-1;
        C[2*i][0]=r;
        C[2*i][1]=1;
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
            z=min(z,max(0,K-k+1)/2);
        if (f==-1){
            k+=1;
            r-=1;
        }
        else{
            k-=1;
            l+=1;
        }
        if (k+min(l,r)*2>=K)
            z=min(z,max(0,K-k+1)/2);
    }

    cout << z;
    return 0;
}
