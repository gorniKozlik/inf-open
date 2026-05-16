n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=list(map(int,input().split()))
W=[n]*(n+1)
C=[]
for l,r in A:
    C.append(l)
    C.append(r)
A.sort()
def f(k,A,D):
    Q=[]
    z=0
    for l,r in A:
        Q.append([l,-1])
        Q.append([r,1])
    for l,r in D:
        Q.append([l,-1])
        Q.append([r,1])
    Q.sort()
    e=0
    for x,w in Q:
        e-=w
        z=max(z,e)
    W[z]=min(k,W[z])
    if not A: return
    for i in range(len(A)):
        for j in range(i+1,len(A)):
            l1,r1,l2,r2=A[i][0],A[i][1],A[j][0],A[j][1]
            l1,r1,l2,r2=l1,r2,r1,l2
            A0=[list(a) for a in A]
            A0.pop(i)
            A0.pop(j-1)
            D0=[list(d) for d in D]
            D0.append([l1,r1])
            D0.append([l2,r2])
            f(k+1,A0,D0)
            
f(0,A,[])
for k in range(n-1,-1,-1):
    W[k]=min(W[k],W[k+1])
for k in K:
    print(W[k],end=" ")
