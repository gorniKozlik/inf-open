n,q=map(int,input().split())
C=[]
for _ in range(n):
    l,r=map(int,input().split())
    C.append([l,-1])
    C.append([r,1])
K=int(input())
C.sort()
l,r,k=0,n,0
z=n
for c,f in C:
    if k+min(l,r)*2>=K:
        z=min(z,max(0,K-k+1)//2)
    if f==-1:
        k+=1
        r-=1
    else:
        k-=1
        l+=1
    e=min(l,r)+1
    if k+min(l,r)*2>=K:
        z=min(z,max(0,K-k+1)//2)
print(z)
