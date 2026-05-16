n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=list(map(int,input().split()))
A.sort()
C=[]
for l,r in A:
    C.append([l,-1])
    C.append([r,1])
C.sort()
l,r,k=0,n,0
D=dict()
for c,f in C:
    D[k]=max(D.get(k,0),min(l,r))
    if f==-1:
        k+=1
        r-=1
    else:
        k-=1
        l+=1
    D[k]=max(D.get(k,0),min(l,r))
D=list(D.items())
D.sort(key=lambda x:x[0]+x[1]*2)
n=len(D)
F=[0]*n
F[n-1]=D[n-1][0]
for i in range(n-2,-1,-1):
    F[i]=max(F[i+1],D[i][0])
for k in K:
    l,r=-1,n-1
    while l<r-1:
        m=(l+r)//2
        if D[m][0]+D[m][1]*2<k:
            l=m
        else:
            r=m
    print(max(0,k-F[r]+1)//2,end=" ")








        
    
    
