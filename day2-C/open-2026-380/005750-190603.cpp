#include <iostream>

using namespace std;

int main()
{
    int T,n,m;
    cin>>T;
    cin>>n>>m;
    if (m==2)
        cout<<"Yes";
    else if ((m==2)&&(n%3==0))
        cout<<"No";
    else
        cout<<"No";
}
