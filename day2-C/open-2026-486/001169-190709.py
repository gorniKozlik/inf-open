import sys


def main():
    n, q = map(int, sys.stdin.readline().split())
    e = []
    for _ in range(n):
        l, r = map(int, sys.stdin.readline().split())
        e.append((l, 1))
        e.append((r, -1))
    k = list(map(int, sys.stdin.readline().split()))
    e.sort()
    m = [0] * (n + 1)
    c = 0
    s = 2 * n
    for i, (_, t) in enumerate(e, 1):
        d = c + (t == 1)
        a = 1 + min(i - 1, s - i)
        if d > m[a]:
            m[a] = d
        c += t
        a = min(i, s - i)
        if c > m[a]:
            m[a] = c
    for i in range(n - 1, -1, -1):
        if m[i + 1] > m[i]:
            m[i] = m[i + 1]

    r = []
    for x in k:
        d = m[x]
        if d >= x:
            r.append("0")
        else:
            r.append(str((x - d + 1) // 2))
    sys.stdout.writelines(" ".join(r))


if __name__ == '__main__':
    main()
