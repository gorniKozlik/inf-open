n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=int(input())
A.sort()
W=[n]*(n+1)
C=[]
for l,r in A:
    C.append([l,-1])
    C.append([r,1])
C.sort()
l,r,k=0,n,0
z=n
for c,f in C:
    e=min(l,r)+1
    if k+e*2>=K:
        z=min(z,(K-k+1)//2)
    if f==-1:
        k+=1
        r-=1
    else:
        k-=1
        l+=1
    e=min(l,r)+1
    if k+e*2>=K:
        z=min(z,(K-k+1)//2)
print(z)
