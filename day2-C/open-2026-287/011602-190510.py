n, q = map(int, input().split())
for i in range(n):
    x, y = map(int, input().split())
a = list(map(int, input().split()))
for i in range(q):
    print(a[i] // 2, end=' ')