n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=list(map(int,input().split()))
W=[n]*(n+1)
C=[]
for l,r in A:
    C.append(l)
    C.append(r)
C.sort()
A.sort()
for c in C:
    D=[0]*n
    z=0
    for i in range(n):
        if A[i][0]<=c<=A[i][1]:
            z+=1
    k=0
    W[z]=0
    for i in range(n):
        if A[i][0]<c<A[i][1]:
            continue
        for j in range(i+1,n):
            if D[i]==0 and D[j]==0 and A[i][1]<=c<=A[j][0]:
                D[i]=1
                D[j]=1
                k+=1
                if A[i][1]==c or A[j][0]==c:
                    z+=1
                else:
                    z+=2
                W[z]=min(k,W[z])
for k in range(n-1,-1,-1):
    W[k]=min(W[k],W[k+1])
for k in K:
    print(W[k],end=" ")
            
    
    
