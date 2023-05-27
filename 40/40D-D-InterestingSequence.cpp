// url:https://codeforces.com/contest/40/problem/D
// time:2023-04-23 08:46:26
// name:D-InterestingSequence

A = int(input())

pw = 0

while A % 12 == 0 :
    A //= 12
    pw += 1

x, y = 2, 13
p = 1

pos = -1

while x <= A :
    if x == A :
        pos = p
    x, y = y, 13 * y - 12 * x
    p += 1

if pos == -1 :
    print('NO')
    exit()

print('YES')
print(1)
print(pos + 2 * pw)

x, y = 2, 13
p = 1

oth = []

while p <= pos + 2 * pw :
    if (pos - p) % 2 == 0 and pos != p :
        oth.append(x * 12 ** ((pos + 2 * pw - p) // 2))
    x, y = y, 13 * y - 12 * x
    p += 1
print(len(oth))
print(' '.join(map(str, oth)))
