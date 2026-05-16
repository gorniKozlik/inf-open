n,q=map(int,input().split())
A=[list(map(int,input().split())) for _ in range(n)]
K=list(map(int,input().split()))
A.sort()
for k in K:
    print(k//2,end=" ")