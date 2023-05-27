// url:https://codeforces.com/contest/39/problem/J
// time:2023-04-20 14:31:52
// name:J-SpellingCheck

a = input()
b = input()

i = 0
while i < len(b) and a[i] == b[i] :
    i += 1

c = a[:i]+a[i+1:]
if b != c :
    print(0)
    exit()

j = i
while j and a[j - 1] == a[j] :
    j -= 1
ans = list(range(j + 1, i + 2))
print(len(ans))
print(' '.join(map(str, ans)))
