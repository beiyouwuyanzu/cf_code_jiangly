//url:https://codeforces.com/contest/1091/problem/G
//time:2021-07-16 11:16:52
//name:G-NewYearandtheFactorisationCollaboration

from math import gcd
from sys import stdout
from random import randint

n = int(input())

cand = [6,7,3]

for t in range(50) :
    x = randint(0, n - 1)
    print("sqrt", x * x % n)
    stdout.flush()
    y = int(input())
    if x == y :
        continue
    if x < y :
        [x, y] = [y, x]
    x -= y
    cand.append(x)
    cand.append(n // x)

primes = []

while n != 1 :
    p = n
    for x in cand :
        y = gcd(p, x)
        if y != 1 :
            p = y
    for x in cand :
        if x % p == 0 :
            x //= p
    primes.append(p)
    n //= p
    print(p)

print("!", len(primes), " ".join(map(str, primes)))
