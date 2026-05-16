g = input
n, q = map(int, g().split())
s = n + n
e = [0] * s
j = 0
for _ in range(n):
    l, r = map(int, g().split())
    e[j] = l * 2
    e[j + 1] = r * 2 + 1
    j += 2
e.sort()
m = [0] * (n + 1)
c = 0
for i, x in enumerate(e, 1):
    u = s - i
    v = i - 1
    a = 1 + (v if v < u else u)
    d = c + 1 if x % 2 == 0 else c
    if d > m[a]:
        m[a] = d
    c += 1 if x % 2 == 0 else -1
    if i < s:
        a = i if i < u else u
        if c > m[a]:
            m[a] = c
for i in range(n - 1, -1, -1):
    if m[i + 1] > m[i]:
        m[i] = m[i + 1]
k = []
while len(k) < q:
    k += list(map(int, g().split()))
print(' '.join(str(0 if x <= m[x] else (x - m[x] + 1) // 2) for x in k[:q]))
