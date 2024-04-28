k= input().split()
k = [ int(i) for i in k]

c = 0
l = 0 
r = len(k)-1


while( c <= r ):
    if k[c] < 0  :
        k[c], k[l] = k[l], k[c]
        l += 1
        c += 1
    elif k[c] > 0  :
        k[r] , k[c] = k[c], k[r]
        r -= 1
    else :
        c += 1 

print(k)