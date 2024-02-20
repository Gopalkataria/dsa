m = input()
d = {i:[] for i in range(10**9)}

print("INP NOW :")
n = map( int  , input().split() ) 



for i in range(n):
    k = n[i]
    d[k].append(i)

print(d)