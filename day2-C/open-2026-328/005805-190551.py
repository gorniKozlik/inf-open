n,q=map(int,input().split())
a=[]
for i in range(n):
    l,r=map(int,input().split())
    a.append((l,r))
quest=list(map(int,input().split()))
ans=[]
for i in range(q):
    ans.append(q[i]//2)