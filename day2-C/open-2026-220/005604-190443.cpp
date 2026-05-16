#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#define int long long 

struct Event{
    int l;
    int type;
    Event(int l,int type):l(l),type(type){};
    Event() = default;
};


signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
   int n,q;
   std::cin>>n>>q;

   std::vector<Event> a;
   for(int i = 0;i < n;i++){
    int l,r;
    std::cin>>l>>r;

    a.push_back(Event(l,-1));
    a.push_back(Event(r,1));
   }
   std::vector<int> ans(n + 1,1e18);

   std::sort(a.begin(),a.end(),[&](Event a,Event b){
    return std::make_pair(a.l,a.type) < std::make_pair(b.l,b.type);
   });

   int close = 0;
   int open = 0;
   for(int i = 0;i < a.size();i++){
    if(a[i].type == -1){
        open++;
        int already = n - close - open;
        //std::cout<<2 * std::min(close,already) + open<<' '<<std::min(close,already)<<' '<<a[i].l<<' '<<open<<std::endl;

        ans[2 * std::min(close,already) + open] = 
        std::min(ans[2 * std::min(close,already) + open],std::min(close,already));
    }else{
        int already = n - close - open;
      //  std::cout<<2 * std::min(close,already) + open<<' '<<std::min(close,already)<<' '<<a[i].l<<' '<<open<<std::endl;
        ans[2 * std::min(close,already) + open] = 
        std::min(ans[2 * std::min(close,already) + open],std::min(close,already));
        open--;
        close++;
    }
   }
   for(int i = n - 2;i >= 0;i--){
    ans[i] = std::min(std::max(0LL,ans[i + 2] - 1),ans[i]);  
   }
   for(int i = 1;i <= n;i++){
    ans[i] = std::min(ans[i],ans[i - 1] + 1);
   }
   while(q--){
    int k;
    std::cin>>k;
   
    std::cout<<ans[k]<<' ';
   }
}