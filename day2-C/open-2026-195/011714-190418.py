n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=list(map(int,input().split()))
A.sort()
W=[n]*(n+1)
C=[]
for l,r in A:
    C.append([l,-1])
    C.append([r,1])
C.sort()
l,r,k=0,n,0

for c,f in C:
    for i in range(0,min(l,r)+1):
        W[k+i*2]=min(W[k+i*2],i)
    if f==-1:
        k+=1
        r-=1
    else:
        k-=1
        l+=1
    for i in range(0,min(l,r)+1):
        W[k+i*2]=min(W[k+i*2],i)
for k in range(n-1,-1,-1):
    W[k]=min(W[k],W[k+1])
for k in K:
    print(W[k],end=" ")
    
