// url:https://codeforces.com/contest/339/problem/A
// time:2023-04-28 12:54:08
// name:A-HelpfulMaths

a = list(map(int, input().split('+')))
a.sort()
print('+'.join(map(str, a)))
